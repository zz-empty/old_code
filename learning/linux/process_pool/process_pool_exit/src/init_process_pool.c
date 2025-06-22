#include "../include/process_pool.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int init_process_pool(pProcInfo_t pChilds, int childsNum) 
{
    pid_t childPid = 0;
    int sfd[2];

    int i = 0;
    for (i = 0; i < childsNum; ++i) {
        socketpair(AF_LOCAL, SOCK_STREAM, 0, sfd);
        childPid = fork(); 

        if (0 == childPid) {
            close(sfd[1]);
            child_process(sfd[0]);
            exit(0);
        }

        //dad process
        close(sfd[0]);
        pChilds[i]._flag = 0;
        pChilds[i]._pid = childPid;
        pChilds[i]._pipefd = sfd[1];
    }
    return 0;
}
