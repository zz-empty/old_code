#include "../include/head.h"
#include "../include/func.h"
#include "../include/thread_pool.h"

int exit_fds[2];//与进程池类似，采用异步拉起同步的方式，有序使进程退出
void sig_func(int signum){
    printf("signum %d is coming!\n",signum);
    write(exit_fds[1],&signum,4);
}

int main(int argc,char*argv[])
{
    if(argc != 4){
        printf("error args!usage: ./pthread_pool IP PORT THREAD_NUM\n");
        return -1;
    }

    pipe(exit_fds);
    if(fork()){//父进程用来接收信号，发送给子进程完成有序退出机制
        close(exit_fds[0]);
        signal(SIGUSR1,sig_func);
        wait(NULL);
        printf("thread pool closed,child process exit!\n");
        exit(0);
    }
    //子进程用来创建线程池，并负责线程的有序退出
    close(exit_fds[1]);
    int thread_num = atoi(argv[3]);//线程数目
    Thread_pool_t thread_pool;//线程池数据结构
    memset(&thread_pool,0,sizeof(thread_pool));
    //1、初始化线程池
    thread_pool_init(&thread_pool,thread_num);

    //2、启动线程池
    thread_pool_start(&thread_pool);

    //3、tcp初始化，socket，bind，listen
    int sfd = 0;
    tcp_init(argv[1],argv[2],&sfd);

    //4、创建epoll并把sfd和exit_fds[0]添加到epoll的红黑树上
    int epfd = 0;
    epfd = epoll_create(1);
    struct epoll_event evs[2];

    epoll_add(epfd,sfd);
    epoll_add(epfd,exit_fds[0]);

    active_user_node_t user;//记录用户信息
    memset(&user, 0, sizeof(user));
    server_sys sys;//记录当前服务器端系统信息
    memset(&sys, 0, sizeof(sys));
    sys.tcp_sfd = sfd;
    sys.tcp_epfd = epfd;
    //前三个文件描述符是系统规定好的【标准输入、输出、错误】,将其放入活跃用户表并标记其为活跃
    sys.active_user_table[0].connect_fd = STDIN_FILENO;
    sys.active_user_table[1].connect_fd = STDOUT_FILENO;
    sys.active_user_table[2].connect_fd = STDERR_FILENO;
    sys.is_active[0] = 1;
    sys.is_active[1] = 1;
    sys.is_active[2] = 1;

    int new_fd = 0;
    int epoll_ready_num = 0;
    int i = 0;
    int j = 0;

    while(1){
        epoll_ready_num = epoll_wait(epfd,evs,2,-1);
        for(i = 0; i<epoll_ready_num; ++i){
            if(evs[i].data.fd == sfd){//有任务到来时，sfd就绪，main线程接收并将任务转发给空闲的子线程
                for(j = 3; j<MAX_USER; ++j){
                    sys.active_user_table[j].connect_fd = accept(sfd, NULL, NULL);
                    sys.is_active[sys.active_user_table[j].connect_fd] = 1;
                    pNode_t pnew = (pNode_t)calloc(1,sizeof(Node_t));//注意别sizeof指针
                    pnew->new_fd = sys.active_user_table[j].connect_fd;//将new_fd任务放在一个任务结点中
                    pthread_mutex_lock(&thread_pool.que.mutex);//对临界资源的访问注意要加锁
                    que_insert(&thread_pool.que,pnew);//将任务结点放置到任务队列中
                    pthread_mutex_unlock(&thread_pool.que.mutex);
                    pthread_cond_signal(&thread_pool.que.cond);//激活pthread_cond_waiti
                    break;
                }
            }
            else if(evs[i].data.fd == exit_fds[0]){
                epoll_del(epfd,sfd);//监听到退出信号后，应该不再接受新的信号
                close(sfd);
                new_fd = -1;//正常监听到的sfd是不可能为-1的，可以将new_fd为-1的任务结点加到队列，若线程从队列中取到的任务结点new_fd为-1，即可知道应该主动退出
                for(j = 0;j<thread_num; ++j ){
                    pNode_t pnew = (pNode_t)calloc(1,sizeof(Node_t));
                    pnew->new_fd = new_fd;//将new_fd设置为-1放到任务队列中
                    pthread_mutex_lock(&thread_pool.que.mutex);
                    que_insert(&thread_pool.que,pnew);
                    pthread_cond_signal(&thread_pool.que.cond);
                    pthread_mutex_unlock(&thread_pool.que.mutex);
                }
                for(j = 0; j<thread_num; j++){
                    pthread_join(thread_pool.pthid[j],NULL);
                    printf("thread exit!\n");
                }
                exit(0);
            }
        }
    }
    return 0;
}

