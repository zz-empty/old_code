#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include "head.h"

//任务队列节点
typedef struct TaskNode {
    int _clifd; //客户端fd
    struct TaskNode *_pNext;
}TaskNode_t, *pTaskNode_t;

//任务队列
typedef struct TaskQueue {
    int _size;  //队列大小
    pTaskNode_t _pHead; //队头
    pTaskNode_t _pTail; //队尾

    pthread_cond_t _cond; //条件变量
    pthread_mutex_t _mutex; //互斥锁
}TaskQueue_t, *pTaskQueue_t;

//初始化任务队列
int init_TaskQueue(pTaskQueue_t pQueue);
//入队
int push_TaskQueue(pTaskQueue_t pQueue, pTaskNode_t pNew);
//得到队头元素
int get_TaskNode(pTaskQueue_t pQueue, pTaskNode_t *ppGet);

#endif
