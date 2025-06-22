#include "LinkQueue.h"
#include <stdio.h>
#include <stdlib.h>

void queue_show(pQueue_t pQ) 
{
    if (!queue_empty(pQ)) {
        pNode_t pCur = pQ->_front;
        for (; pCur; pCur = pCur->_pNext) {
            printf("%d ", pCur->_data);
        }
        printf("\n");
    }
}

void queue_init(pQueue_t pQ)
{
    pQ->_front = NULL;
    pQ->_back = NULL;
    pQ->_size = 0;
}

void queue_destroy(pQueue_t pQ)
{
    if (pQ->_front) {
        pNode_t pPre = pQ->_front;
        pNode_t pCur = pPre->_pNext;
        for (; pCur; pPre = pCur, pCur = pCur->_pNext) {
            free(pPre);
            pPre = NULL;
        }
        
        pQ->_front = NULL;
        pQ->_back = NULL;
        pQ->_size = 0;
    }
}

int queue_empty(pQueue_t pQ)
{
    return NULL == pQ->_front;
}

int queue_len(pQueue_t pQ)
{
    return pQ->_size;
}

TYPENAME queue_front(pQueue_t pQ)
{
    if (!queue_empty(pQ)) {
        return pQ->_front->_data;
    }
    else {
        return EOF;
    }
}
TYPENAME queue_back(pQueue_t pQ)
{
    if (!queue_empty(pQ)) {
        return pQ->_back->_data;
    }
    else {
        return EOF;
    }
}
int queue_push(pQueue_t pQ, TYPENAME val)
{
    pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
    pNew->_data = val;

    if (queue_empty(pQ)) {
        //如果队列为空
        pQ->_front = pQ->_back = pNew;
    }
    else {
        //队列非空, 尾插
        pQ->_back->_pNext = pNew;
        pQ->_back = pNew;
    }

    ++pQ->_size;
    return 0;
}
int queue_pop(pQueue_t pQ)
{
    if (!queue_empty(pQ)) {
        pNode_t pCur = pQ->_front;
        pQ->_front = pQ->_front->_pNext;
        --pQ->_size;

        //释放队头结点
        free(pCur);
        pCur = NULL;
        return 0;
    }
    return -1;
}
