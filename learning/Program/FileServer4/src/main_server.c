#include "../include/head.h"
#include "../include/thread_pool.h"

//发送信号，实现异步退出线程池
int exitpipe[2];
void sig_func(int sigNum)
{
    printf("sig %d is coming!\n", sigNum);
    write(exitpipe[1], "a", 1);
}

int main(int argc, char *argv[]) 
{
    //配置文件
    ARGS_CHECK(argc, 2);

    //父进程用来接收退出信号
    pipe(exitpipe);
    if (fork()) {
        close(exitpipe[0]);
        signal(SIGUSR1, sig_func);

        //回收子进程的资源
        wait(NULL);
        printf("thread_pool exit!\n");
        exit(0);
    }

    //子进程用来管理线程池
    close(exitpipe[1]);

    //从配置文件中取出服务器ip地址、port端口号、子线程数量
    FILE *fp = fopen(argv[1], "r");
    char ip[128] = {0};
    int port = 0;
    int thread_num = 0;
    fscanf(fp, "%s%d%d", ip, &port, &thread_num);
    fclose(fp);

    //创建线程池，并初始化
    ThreadPool_t pool;
    init_ThreadPool(&pool, thread_num);

    //启动线程池
    boot_ThreadPool(&pool);

    //创建一个正在监听的tcp套接字
    int sfd = tcp_init(ip, port);

    //处理客户端的请求，和退出请求
    //有新请求就新建任务节点，放入任务队列
    //子线程等待任务，有任务立刻处理
    if (-1 != sfd) {
        interact_cli(sfd, &pool, exitpipe[0]);
    }

    return 0;
}
