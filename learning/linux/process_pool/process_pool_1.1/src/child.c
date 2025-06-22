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

int childFunc(int pipeFd) 
{
    printf("child_process already created, pid = %d\n", getpid());

    int clientFd = 0;
    while (1) {
        //receive client_fd
        recvFd(pipeFd, &clientFd);

        //working
        send(clientFd, "helloclient", 11, 0);
        while(1);

        //done and inform dad
        write(pipeFd, "a", 1);
    } 
    return 0;
}
