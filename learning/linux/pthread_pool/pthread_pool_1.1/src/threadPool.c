#include "../include/head.h"
#include "../include/threadPool.h"
#include "../include/taskque.h"

void cleanFunc(void *p)
{
    pQue_t pQue = (pQue_t)p;
    //unlock
    pthread_mutex_unlock(&pQue->mutex);
}

void *threadFunc(void *p)
{
    pQue_t pQue = (pQue_t)p;
    pNode_t pCur;
    int ret;

    while (1) {
        pthread_mutex_lock(&pQue->mutex);
        //pthread clean
        pthread_cleanup_push(cleanFunc, pQue);

        //if taskque is empty, wait
        if (0 == pQue->size) {
            printf("thread begin wait!\n");
            pthread_cond_wait(&pQue->cond, &pQue->mutex);
        }
        //get taskque node 
        ret = getTaskNode(pQue, &pCur);
        pthread_mutex_unlock(&pQue->mutex);

        //working
        if (0 == ret) {
           transFile(pCur->clientFd); 
           printf("------------------------transFile finish!\n");
           //release taskque_node
           free(pCur);
           pCur = NULL;
        }

        pthread_cleanup_pop(1);
    }
    pthread_exit(NULL);
}

int threadPoolInit(pThreadPool_t pPool, int threadNum)
{
    pPool->threadNum = threadNum;
    pPool->pThid = (pthread_t*)calloc(threadNum, sizeof(pthread_t));
    queInit(&pPool->que);
    return 0;
}

int threadPoolBoot(pThreadPool_t pPool)
{
    //loop create pthread
    int i = 0;
    for (i = 0; i < pPool->threadNum; ++i) {
        pthread_create(pPool->pThid + 1, NULL, threadFunc, &pPool->que);
    }
    return 0;
}

