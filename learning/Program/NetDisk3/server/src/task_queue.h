#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include "head.h"
#include "func.h"

//任务队列节点
typedef struct TaskNode {
    socket_t _clifd; //客户端套接字
    struct TaskNode *_pNext;
}TaskNode_t, *pTaskNode_t;

//任务队列
typedef struct TaskQueue {
    int _size;  //队列大小
    pTaskNode_t _pHead; //队头
    pTaskNode_t _pTail; //队尾

    pthread_cond_t _cond; //条件变量
    pthread_mutex_t _mutex; //互斥锁
    char _flag; //线程退出标志（0-不退出 1-退出）
}TaskQueue_t, *pTaskQueue_t;

int init_TaskQueue(pTaskQueue_t pQueue); //初始化任务队列
int push_TaskQueue(pTaskQueue_t pQueue, pTaskNode_t pNew);//入队
int get_TaskNode(pTaskQueue_t pQueue, pTaskNode_t *ppGet);//得到队头元素，同时出队

#endif
