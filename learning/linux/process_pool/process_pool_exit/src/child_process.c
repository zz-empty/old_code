#include "../include/process_pool.h"
#include <stdio.h>
#include <unistd.h>

int child_process(int pipeFd) 
{
    printf("child_process already created, pid = %d\n", getpid());

    int clientFd = 0;
    while (1) {
        //receive client_fd
        recvFd(pipeFd, &clientFd);

        //working
        /* printf("transfer start!\n"); */
        char filename[] = "file";
        send_file(clientFd, filename);
        printf("transfer finish!\n");

        //done and inform dad
        close(clientFd);
        write(pipeFd, "a", 1);
    } 
    return 0;
}
