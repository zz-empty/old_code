#ifndef __SEQQUEUE_H__
#define __SEQQUEUE_H__

#define TYPENAME int

typedef struct Queue {
    TYPENAME *_pdata;	//队列
    int _size;		//队列大小
    int _front;		//队头
    int _back;		//队尾
}Queue_t, *pQueue_t;

void queue_init(pQueue_t pQ, int size);
void queue_destroy(pQueue_t pQ);
int queue_empty(pQueue_t pQ);
int queue_full(pQueue_t pQ);
int queue_len(pQueue_t pQ);
TYPENAME queue_front(pQueue_t pQ);
TYPENAME queue_back(pQueue_t pQ);
int queue_push(pQueue_t pQ, TYPENAME val);
int queue_pop(pQueue_t pQ);
void queue_show(pQueue_t pQ);


#endif
