#include "../include/process_pool.h"
#include <stdio.h>                                                                                                                                         
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int exitPipe[2];
void sigFunc(int sigNum)
{
    printf("sig is comming!\n");
    write(exitPipe[1], &sigNum, 4);
}

int main(int argc, char *argv[]) 
{

    //配置文件
    ARGS_CHECK(argc, 2);
    FILE *fp = fopen(argv[1], "r");
    char ip[128] = {0};
    int port = 0;
    int childsNum = 0;
    fscanf(fp, "%s%d%d", ip, &port, &childsNum);
    fclose(fp);

    //创建子进程数组
    pProcInfo_t pChilds = (pProcInfo_t)calloc(childsNum, sizeof(ProcInfo_t));

    //创建进程池
    init_process_pool(pChilds, childsNum);

    //main register pool_exit signal
    pipe(exitPipe);
    signal(SIGUSR1, sigFunc);

    //2.create tcp_socket to listen
    int sfd = tcp_init(ip, port);

    interact_cli(sfd, pChilds, childsNum, exitPipe[0]);

    free(pChilds);
    pChilds = NULL;
    return 0;
}

