#ifndef __TASKQUE_H__
#define __TASKQUE_H__
#include "head.h"

//tesk_queue node data_structure
typedef struct Node {
    int clientFd;
    struct Node *pNext;
}Node_t, *pNode_t;

//test_queue data_structure
typedef struct {
    int size;//队列长度
    pNode_t pHead;
    pNode_t pTail;
    pthread_cond_t cond;//条件变量
    pthread_mutex_t mutex;//互斥锁
}Que_t, *pQue_t;

int queInit(pQue_t pQue);
int queInsert(pQue_t pQue, pNode_t pNew);
int getTaskNode(pQue_t pQue, pNode_t* pGet);

#endif
