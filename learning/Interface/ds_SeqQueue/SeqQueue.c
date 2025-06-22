#include "SeqQueue.h"
#include <stdio.h>
#include <stdlib.h>

void queue_show(pQueue_t pQ) 
{
    if (!queue_empty(pQ)) {
        for (int i = pQ->_front; i != pQ->_back; i = (i + 1) % pQ->_size) {
            printf("%d ", pQ->_pdata[i]);
        }
        printf("\n");
    }
}

void queue_init(pQueue_t pQ, int size)
{
    pQ->_pdata = (TYPENAME*)calloc(size, sizeof(TYPENAME));
    pQ->_size = size;
    pQ->_front = 0;
    pQ->_back = 0;
}
void queue_destroy(pQueue_t pQ)
{
    if (pQ->_pdata) {
        free(pQ->_pdata);
        pQ->_pdata = NULL;
        pQ->_front = 0;
        pQ->_back = 0;
    }
}
int queue_empty(pQueue_t pQ)
{
    return pQ->_front == pQ->_back;
}
int queue_full(pQueue_t pQ)
{
    return (pQ->_back + 1) % pQ->_size == pQ->_front;
}
int queue_len(pQueue_t pQ)
{
    int len = 0;
    if (!queue_empty(pQ)) {
        int start = pQ->_front;
        for (; start != pQ->_back; start = (start + 1) % pQ->_size) {
            ++len;
        }
    }
    return len;
}
TYPENAME queue_front(pQueue_t pQ)
{
    if (!queue_empty(pQ)) {
        return pQ->_pdata[pQ->_front];
    }
    else {
        return EOF;
    }
}
TYPENAME queue_back(pQueue_t pQ)
{
    if (!queue_empty(pQ)) {
        return pQ->_pdata[pQ->_back - 1];
    }
    else {
        return EOF;
    }
}
int queue_push(pQueue_t pQ, TYPENAME val)
{
    if (!queue_full(pQ)) {
        pQ->_pdata[pQ->_back] = val;
        pQ->_back = (pQ->_back + 1) % pQ->_size;
        return 0;
    }
    return -1;
}
int queue_pop(pQueue_t pQ)
{
    if (!queue_empty(pQ)) {
        pQ->_front = (pQ->_front + 1) % pQ->_size;
        return 0;
    }
    return -1;
}
