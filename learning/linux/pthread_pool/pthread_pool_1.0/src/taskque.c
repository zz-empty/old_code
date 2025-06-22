#include "../include/head.h"
#include "../include/taskque.h"

int queInit(pQue_t pQue)
{
    pQue->size = 0;
    pQue->pHead = pQue->pTail = NULL;
    pthread_cond_init(&pQue->cond, NULL);
    pthread_mutex_init(&pQue->mutex, NULL);
    return 0;
}

int queInsert(pQue_t pQue, pNode_t pNew)
{
    //main already locked

    //insert taskque
    if (NULL == pQue->pHead) {
        pQue->pHead = pQue->pTail = pNew;
    }
    else {
        pQue->pTail->pNext = pNew;
        pQue->pTail = pNew;
    }
    //increase taskque len
    ++pQue->size;
    return 0;
}

int getTaskNode(pQue_t pQue, pNode_t* pGet)
{
    //child_pthread already locked

    //if taskque is empty
    if (!pQue->size) {
        return -1;
    }

    *pGet = pQue->pHead;
    pQue->pHead = pQue->pHead->pNext;

    //update taskque size
    --pQue->size;

    //check taskque whether is empty
    if (0 == pQue->size) {
        pQue->pTail = NULL;
    }
    return 0;
}
