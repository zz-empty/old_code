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
    int size;
    pNode_t pHead;
    pNode_t pTail;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}Que_t, *pQue_t;

int queInit(pQue_t pQue);
int queInsert(pQue_t pQue, pNode_t pNew);
int getTaskNode(pQue_t pQue, pNode_t* pGet);

#endif
