#include "../include/process_pool.h"
#include "../include/process_pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//与主进程通信的管道,用来传递信号
int exitpipe[2];

//退出信号处理,通知主进程退出
void sigFunc(int sigNum)
{
    /* printf("%d is coming!\n", sigNum); */ 
    write(exitpipe[1], &sigNum, 4);
}

int main(int argc, char *argv[]) 
{
    //命令行参数：配置文件（ip地址，port端口号，子进程数量）
    ARGS_CHECK(argc, 2);

    //从配置文件中拿到ip，port，子进程数
    char ip[64] = {0};
    int port = 0;
    int childsNum = 0;
    FILE *fp = fopen(argv[1], "r");
    ERROR_CHECK(fp, NULL, "fopen");
    fscanf(fp, "%s%d%d", ip, &port, &childsNum);
    fclose(fp);

    //创建一个数组，存储子进程信息
    pProcInfo_t pChilds = (pProcInfo_t)calloc(childsNum, sizeof(ProcInfo_t));

    //创建进程池（参数：子进程数组，子进程数量）
    init_process_pool(pChilds, childsNum);

    //注册退出信号, SIGUSR1默认行为是终止进程
    pipe(exitpipe);
    signal(SIGUSR1, sigFunc);

    //建立一个tcp类型正在监听的套接字
    int sfd = tcp_init(ip, port);

    //处理来自客户端，进程池，退出信号的请求
    if (-1 != sfd) {
        interact_cli(sfd, pChilds, childsNum, exitpipe[0]);
    }

    //回收子进程数组
    free(pChilds);
    pChilds = NULL;
    return 0;
}
