#include "../include/head.h"
#include "../include/task_queue.h"

//初始化任务队列
int init_TaskQueue(pTaskQueue_t pQueue)
{
    pQueue->_size = 0;
    pQueue->_pHead = pQueue->_pTail = NULL;
    pthread_cond_init(&pQueue->_cond, NULL);
    pthread_mutex_init(&pQueue->_mutex, NULL);
    pQueue->_flag = 0;
    return 0;
}

//入队
int push_TaskQueue(pTaskQueue_t pQueue, pTaskNode_t pNew)
{
    if (NULL == pQueue->_pHead) {
        pQueue->_pHead = pQueue->_pTail = pNew;
    }
    else {
        pQueue->_pTail->_pNext = pNew;
        pQueue->_pTail = pNew;
    }

    ++pQueue->_size;
    return 0;
}

//得到队头元素
int get_TaskNode(pTaskQueue_t pQueue, pTaskNode_t *ppGet)
{
    //没有元素
    if (0 == pQueue->_size) {
        return -1;
    }

    //有元素，取出，更新队头
    *ppGet = pQueue->_pHead;
    pQueue->_pHead = pQueue->_pHead->_pNext;

    //只有一个元素，更新队尾
    if (1 == pQueue->_size) {
        pQueue->_pTail = NULL;
    }
    
    //减小队列长度
    --pQueue->_size;
    return 0;
}
