#include "../include/process_pool.h"

int exitPipe[2];
void sigFunc(int sigNum)
{
    printf("sig is comming!\n");
    write(exitPipe[1], &sigNum, 4);
}

int main(int argc, char *argv[]) 
{

    //args: ip port processNum
    ARGS_CHECK(argc, 4);
    //init data
    int processNum = atoi(argv[3]);
    pProcess_data_t pData = (pProcess_data_t)calloc(processNum, sizeof(process_data_t));

    //1.loop create child_fds
    makeChilds(processNum, pData);

    //main register pool_exit signal
    pipe(exitPipe);
    signal(SIGUSR1, sigFunc);

    //2.create tcp_socket to listen
    int sfd = 0;
    tcpInit(argv[1], argv[2], &sfd);

    //3.create epoll to manage fds
    int epfd = epoll_create(1);
    //add sfd to epoll
    epollAddFd(sfd, epfd);
    //add child_fd to epoll
    int i = 0;
    for (i = 0; i < processNum; ++i) {
        epollAddFd(pData[i].pipeFd, epfd);
    }
    //add exitPipe to epoll
    epollAddFd(exitPipe[0], epfd);

    //4.listen client require
    int readyNum = 0;
    struct epoll_event evs[2];
    memset(evs, 0, sizeof(evs));
    int newFd = 0;

    while (1) {
        readyNum = epoll_wait(epfd, evs, 2, -1);

        for (i = 0; i < readyNum; ++i) {
            if (evs[i].data.fd == sfd) {
                //client require
                newFd = accept(sfd, NULL, NULL);
                //search free child_process
                int j = 0;
                for (j = 0; j < processNum; ++j) {
                    if (0 == pData[j].flag) {
                        printf("-----------------client require! assign to child_%d and busy-------------------\n", pData[j].pid);
                        //assign tesk to free child_process, child_exitFlag=0
                        sendFd(pData[j].pipeFd, newFd, 0);
                        //update child_process state to busy
                        pData[j].flag = 1;
                        break;
                    }
                }
                close(newFd);
            }
            else if (evs[i].data.fd == exitPipe[0]) {
                int j = 0;
                //child_process exit
                for (j = 0; j < processNum; ++j) {
                    //set child_exitFlag=1
                    sendFd(pData[j].pipeFd, 0, 1);
                }

                //Recycling child_resources
                for (j = 0; j < processNum; ++j) {
                    int status;
                    wait(&status);
                    if (WIFEXITED(status)) {
                        printf("exit num = %d\n", WEXITSTATUS(status));
                    }
                }

                //main_process exit
                printf("main exit!\n");
                exit(0);
            }
            else {
                //check Child_pipeFd, if ready than set child_process to free
                int j = 0;
                for (j = 0; j < processNum; ++j) {
                    if (evs[i].data.fd == pData[i].pipeFd && pData[i].flag == 1) {
                        printf("child_%d pipeFd ready!\n", pData[j].pid);
                        char buf[4] = {0};
                        read(pData[i].pipeFd, buf, sizeof(buf));
                        pData[i].flag = 0;

                        printf("---------------------------child_%d is free-------------------------------------\n", pData[j].pid);
                    }
                }
                /* printf("check over!\n"); */
            }
        }
    }
    return 0;
}

