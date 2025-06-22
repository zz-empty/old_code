#include "head.h"
#include "func.h"
#include "thread_pool.h"

//信号处理函数，实现异步退出线程池
//父进程收到信号后，通知子进程处理
int exitpipe[2];
void sig_handle(int signum)
{
    printf("signal [%d] is comming!\n", signum);
    write(exitpipe[1], &signum, 4);
}

int main(int argc, char *argv[]) 
{
    //参数：配置文件路径
    if (2 != argc) {
        fprintf(stderr, "Args error!\n");
        return -1;
    }

    //建立父子通信的管道，父进程写exitpipe[1]，子进程读exitpipe[0]
    pipe(exitpipe);

    //父进程用来接收退出信号
    if (fork()) {
        printf("main pid: %d\n", getpid());

        close(exitpipe[0]);
        //注册退出信号
        signal(SIGUSR1, sig_handle);
        
        //回收子进程资源，退出程序
        wait(NULL);
        printf("The thread_pool was already closed, all child_thread were exited!\n");
        exit(0);
    }

    //子进程管理各种请求：客户端，线程池，退出管道
    printf("child pid: %d\n", getpid());
    close(exitpipe[1]);

    //从配置文件中拿到 服务器ip和port,线程数量
    char ip[16] = "";
    int port = 0;
    int thread_num = 0;
    conf_get(argv[1], ip, &port, &thread_num);
    printf("ip:%s, port:%d, thread_num:%d\n", ip, port, thread_num);

    //建立tcp监听
    socket_t fd_server = tcp_init(ip, port);
    EXIT_CHECK(fd_server, -1, "socket_init");
    printf("DiskServer[ip:%s, port:%d] boot...\n", ip, port);

    //建立线程池并启动
    ThreadPool_t pool;
    init_ThreadPool(&pool, thread_num);
    boot_ThreadPool(&pool);
    printf("The thread_pool is already boot!\n");

    //将服务器套接字，退出管道加入epoll管理
    int epfd = epoll_create(1);
    epoll_add(fd_server, epfd);
    epoll_add(exitpipe[0], epfd);

    //监听epfd
    int ready_fd_num = 0;
    struct epoll_event evs[2];
    socket_t fd_client;
    while (1) {
        ready_fd_num = epoll_wait(epfd, evs, 2, -1);

        for (int i = 0; i < ready_fd_num; ++i) {
            if (evs[i].data.fd == fd_server) {
                //有新客户连接, 加入任务队列，通知子线程
                fd_client = accept(fd_server, NULL, NULL);
                pTaskNode_t pNew = (pTaskNode_t)calloc(1, sizeof(TaskNode_t));
                pNew->_clifd = fd_client;

                pthread_mutex_lock(&pool._que._mutex);//加锁
                push_TaskQueue(&pool._que, pNew);//入队
                pthread_cond_signal(&pool._que._cond);//通知子线程处理
                pthread_mutex_unlock(&pool._que._mutex);//解锁
            }

            else if (evs[i].data.fd == exitpipe[0]) {
                //父进程发来退出通知, 读取管道
                int signum;
                read(exitpipe[0], &signum, 4);
                printf("receive signal [%d] , ready exit!\n", signum);

                //将退出标志置位，唤醒所有线程，让它们退出
                pool._que._flag = 1;
                pthread_cond_broadcast(&pool._que._cond);

                //关闭线程池，回收线程池资源
                close_ThreadPool(&pool);
                puts("close thread_pool");
                destory_ThreadPool(&pool);
                puts("destory thread_pool");
                puts("over");

                //退出程序
                exit(0);
            }
        }
    }
    
    return 0;
}
