#include "../include/process_pool.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include <sys/socket.h>
#include <sys/epoll.h>

int epollAddFd(int fd, int epfd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    return 0;
}

int interact_cli(int sfd, pProcInfo_t pChilds, int childsNum, int exitpipe)
{
    //3.create epoll to manage fds
    int epfd = epoll_create(1);
    //add sfd to epoll
    epollAddFd(sfd, epfd);
    //add child_fd to epoll
    int i = 0;
    for (i = 0; i < childsNum; ++i) {
        epollAddFd(pChilds[i]._pipefd, epfd);
    }
    //add exitpipe to epoll
    epollAddFd(exitpipe, epfd);

    //4.listen client require
    int readyFdNum = 0;
    struct epoll_event evs[2];
    memset(evs, 0, sizeof(evs));
    int newfd = 0;

    while (1) {
        readyFdNum = epoll_wait(epfd, evs, 2, -1);

        for (i = 0; i < readyFdNum; ++i) {
            if (evs[i].data.fd == sfd) {
                //client require
                newfd = accept(sfd, NULL, NULL);
                //search free child_process
                int j = 0;
                for (j = 0; j < childsNum; ++j) {
                    if (0 == pChilds[j]._flag) {
                        printf("-----------------client require! assign to child_%d and busy-------------------\n", pChilds[j]._pid);
                        //assign tesk to free child_process
                        sendFd(pChilds[j]._pipefd, newfd);
                        //update child_process state to busy
                        pChilds[j]._flag = 1;
                        break;
                    }
                }
                close(newfd);
            }
            else if (evs[i].data.fd == exitpipe) {
                int j = 0;
                //let child_process exit
                for (j = 0; j < childsNum; ++j) {
                    kill(pChilds[j]._pid, SIGUSR1);
                }

                //Recycling child_resources
                for (j = 0; j < childsNum; ++j) {
                    wait(NULL);
                }

                //main_process exit
                printf("main exit!\n");
                exit(0);
            }
            else {
                //check Child_pipeFd, if ready than set child_process to free
                int j = 0;
                for (j = 0; j < childsNum; ++j) {
                    if (evs[i].data.fd == pChilds[j]._pipefd && pChilds[j]._flag == 1) {
                        printf("child_%d pipeFd ready!\n", pChilds[j]._pid);
                        char buf[4] = {0};
                        read(pChilds[j]._pipefd, buf, sizeof(buf));
                        pChilds[j]._flag = 0;

                    }
                }
                /* printf("check over!\n"); */
            }
        }
    }
}
