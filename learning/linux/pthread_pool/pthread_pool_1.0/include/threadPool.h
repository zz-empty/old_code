#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "head.h"
#include "taskque.h"

typedef struct {
    int data_len;
    char buf[1000];
}Train_t, *pTrain_t;

//threadpool data_structure
typedef struct {
    int threadNum;//线程池中的线程数量
    pthread_t *pThid;//线程数组
    Que_t que;//任务队列(生产、消费)
}ThreadPool_t, *pThreadPool_t;

int threadPoolInit(pThreadPool_t pPool, int threadNum);
int threadPoolBoot(pThreadPool_t pPool);

int transFile(int clientFd);
int tcpInit(char *ip, char *port, int *sockFd);
int epollAddFd(int fd, int epfd);

#endif
