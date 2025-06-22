#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "head.h"
#include "task_queue.h"

//线程池
typedef struct {
    int _thread_num; //子线程数量
    pthread_t *_pthid;  //子线程数组
    TaskQueue_t _que;   //任务队列
}ThreadPool_t, *pThreadPool_t;

int init_ThreadPool(pThreadPool_t pPool, int thread_num);   //初始化线程池
int boot_ThreadPool(pThreadPool_t pPool);   //启动线程池
int close_ThreadPool(pThreadPool_t pPool);  //关闭线程池
int destory_ThreadPool(pThreadPool_t pPool);                //销毁线程池

#endif
