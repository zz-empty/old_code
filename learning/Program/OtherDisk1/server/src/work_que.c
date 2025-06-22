#include "../include/head.h"
#include "../include/work_que.h"

int que_init(pQue_t pque)
{
    memset(pque,0,sizeof(Que_t));//清空队列结构体
    pthread_mutex_init(&pque->mutex,NULL);//初始化线程锁
    pthread_cond_init(&pque->cond,NULL);//初始化条件变量
    return 0;
}
int que_insert(pQue_t pque,pNode_t pnew){
    //如果队列为空，则队列的头尾指针都指向这个新的结点
    if(!pque->que_size){
        pque->que_head = pnew;
        pque->que_tail = pnew;
    }//如果队列不为空，采用尾插法插入结点
    else{
        pque->que_tail->pNext = pnew;
        pque->que_tail = pnew;
    }
    pque->que_size ++;
    return 0;
}

int que_get(pQue_t pque,pNode_t *ppcur){
    if(!pque->que_size){
        return -1;
    }
    //头部删除法从队列中取元素
    *ppcur = pque->que_head;
    pque->que_head = pque->que_head->pNext;
    pque->que_size --;

    if(!pque->que_size){
        pque->que_tail = NULL;
    }
    return 0;
}
