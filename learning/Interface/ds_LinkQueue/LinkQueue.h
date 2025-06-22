#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#define TYPENAME int

//链队节点
typedef struct Node {
    TYPENAME _data;
    struct Node *_pNext;
}Node_t, *pNode_t;

//链队
typedef struct Queue {
    pNode_t _front;		//队头
    pNode_t _back;		//队尾
    int _size;		//队列长度
}Queue_t, *pQueue_t;


void queue_init(pQueue_t pQ);
void queue_destroy(pQueue_t pQ);
int queue_empty(pQueue_t pQ);
int queue_len(pQueue_t pQ);
TYPENAME queue_front(pQueue_t pQ);
TYPENAME queue_back(pQueue_t pQ);
int queue_push(pQueue_t pQ, TYPENAME val);
int queue_pop(pQueue_t pQ);
void queue_show(pQueue_t pQ);


#endif
