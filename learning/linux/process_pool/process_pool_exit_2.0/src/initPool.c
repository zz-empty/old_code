#include "../include/process_pool.h"

int makeChilds(int processNum, pProcess_data_t pData) 
{
    pid_t childPid = 0;
    int sfd[2];

    int i = 0;
    for (i = 0; i < processNum; ++i) {
        socketpair(AF_LOCAL, SOCK_STREAM, 0, sfd);
        childPid = fork(); 

        if (0 == childPid) {
            close(sfd[1]);
            childFunc(sfd[0]);
            exit(0);
        }

        //dad process
        close(sfd[0]);
        pData[i].flag = 0;
        pData[i].pid = childPid;
        pData[i].pipeFd = sfd[1];
    }
    return 0;
}
