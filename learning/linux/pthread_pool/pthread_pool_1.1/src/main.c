#include "../include/head.h"
#include "../include/threadPool.h"

int exitPipe[2];
void sigFunc(int sigNum)
{
    printf("sig is comming!\n");
    write(exitPipe[1], &sigNum, 4);

}

int main(int argc, char *argv[]) 
{
    //create pipe to exit
    pipe(exitPipe);

    if (fork()) {
        //dad recv exit_signal write pipe
        close(exitPipe[0]);
        signal(SIGUSR1, sigFunc);

        //wait son
        wait(NULL);
        printf("child exit!\n");
        //dad exit
        exit(0);
    }

    close(exitPipe[1]);
    
    //args: ip port threadNum
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
    epollAddFd(exitPipe[0], epfd);


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
            if (evs[i].data.fd == exitPipe[0]) {
                //recv SIGNAL and exit all thread
                int j = 0;
                for (j = 0; j < threadNum; ++j) {
                    pthread_cancel(pool.pThid[j]);
                }

                //recycling resource
                for (j = 0; j < threadNum; ++j) {
                    pthread_join(pool.pThid[j], NULL);
                }

                //exit chile_process
                exit(0);
            }
        }
    }
    return 0;
}

