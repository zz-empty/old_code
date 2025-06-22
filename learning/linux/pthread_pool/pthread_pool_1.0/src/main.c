#include "../include/head.h"
#include "../include/threadPool.h"

int main(int argc, char *argv[]) 
{
    // exe ip port threadNum
    ARGS_CHECK(argc, 4);
    int threadNum = atoi(argv[3]);

    //1. create threadPool
    ThreadPool_t pool;
    memset(&pool, 0, sizeof(pool));

    //2. init threadPool
    threadPoolInit(&pool, threadNum);

    //3. boot threadPool
    threadPoolBoot(&pool);

    //4. create socket to listen client require
    int sfd = 0;
    tcpInit(argv[1], argv[2], &sfd);

    //5. create epoll to monitoring fds
    int epfd = epoll_create(1);

    epollAddFd(sfd, epfd);

    int readyNum = 0;
    struct epoll_event evs[2];
    int clientFd = 0;
    while (1) {
        readyNum = epoll_wait(epfd, evs, 2, -1);
        int i = 0;
        for (i = 0; i < readyNum; ++i) {
            if (evs[i].data.fd == sfd) {
                //get clientFd
                clientFd = accept(sfd, NULL, NULL);
                printf("client connect!\n");

                //add clientFd to taskque
                pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));

                pthread_mutex_lock(&pool.que.mutex);

                pNew->clientFd = clientFd;
                queInsert(&pool.que, pNew);
                //awake pthread
                pthread_cond_signal(&pool.que.cond);

                pthread_mutex_unlock(&pool.que.mutex);
            }
        }
    }
    return 0;
}

