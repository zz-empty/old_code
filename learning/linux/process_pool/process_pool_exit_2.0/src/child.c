#include "../include/process_pool.h"

int childFunc(int pipeFd) 
{
    printf("child_process already created, pid = %d\n", getpid());

    char exitFlag = 0;
    int clientFd = 0;
    while (1) {
        //receive client_fd
        recvFd(pipeFd, &clientFd, &exitFlag);
        if (1 == exitFlag) {
            printf("child exit\n");
            exit(99);
        }

        //working
        /* printf("transfer start!\n"); */
        transFile(clientFd);
        printf("transfer finish!\n");

        //done and inform dad
        close(clientFd);
        write(pipeFd, "a", 1);
    } 
    return 0;
}
