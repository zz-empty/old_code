#ifndef __WORK_QUE__
#define __WORK_QUE__
#include"head.h"

//任务结点的数据结构
typedef struct tag_node{
    int new_fd;
    struct tag_node *pNext;
}Node_t, *pNode_t;

//任务队列的数据结构
typedef struct{
    int que_size;
    pNode_t que_head,que_tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Que_t,*pQue_t;

int que_init(pQue_t pque);
int que_insert(pQue_t pque,pNode_t pnew);
int que_get(pQue_t pque,pNode_t *ppcur);

#endif

