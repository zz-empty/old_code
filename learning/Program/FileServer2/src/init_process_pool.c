#include "../include/process_pool.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

//功能：创建进程池
//参数：子进程数组，子进程数量
int init_process_pool(pProcInfo_t pChilds, int childsNum)
{
    pid_t pid = 0;
    int fds[2];//存储socketpair创建的一对套接口

    //创建childsNum个子进程
    int i;
    for (i = 0; i < childsNum; ++i) {
        //通过socketpair创建一对本地的tcp类型的套接口
        socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
        pid = fork();

        //启动子进程
        if (0 == pid) {
            close(fds[1]);
            child_process(fds[0]);
            exit(0);
        }

        //主进程记录子进程的信息
        close(fds[0]);
        pChilds[i]._pid = pid;
        pChilds[i]._flag = 0;
        pChilds[i]._pipefd = fds[1];
    }

    return 0;
}
