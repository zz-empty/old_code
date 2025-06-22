#include "../include/process_pool.h"

int main(int argc, char *argv[]) 
{
    //ip port processNum
    ARGS_CHECK(argc, 4);
    //init data
    int processNum = atoi(argv[3]);
    pProcess_data_t pData = (pProcess_data_t)calloc(processNum, sizeof(process_data_t));

    //1.循环创建子进程
    makeChilds(processNum, pData);

    //2.create tcp_socket to listen
    int sfd = 0;
    tcpInit(argv[1], argv[2], &sfd);

    //3.create epoll to manage fds
    int epfd = epoll_create(1);
    epollAddFd(sfd, epfd);

    int i = 0;
    for (i = 0; i < processNum; ++i) {
        epollAddFd(pData[i].pipeFd, epfd);
    }

    //4.listen client require
    int readyNum = 0;
    struct epoll_event evs[2];
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
                        printf("client require! assign to %d\n", pData[j].pid);
                        //assign tesk to free child_process
                        sendFd(pData[j].pipeFd, newFd);
                        //update child_process state to busy
                        pData[j].flag = 1;
                        break;
                    }
                }
                close(newFd);
            }
            else {
                //check pipeFd, if ready and set child_process to free
                int j = 0;
                for (j = 0; j < processNum; ++j) {
                    if (evs[i].data.fd == pData[i].pipeFd) {
                        char buf[4] = {0};
                        read(pData[i].pipeFd, buf, sizeof(buf));
                        printf("%d free\n", pData[j].pid);
                        pData[i].flag = 0;
                    }
                }
            }
        }
    }
    return 0;
}

