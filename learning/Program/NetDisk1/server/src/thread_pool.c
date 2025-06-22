#include "head.h"
#include "func.h"
#include "thread_pool.h"
#include "task_queue.h"

//初始化线程池
int init_ThreadPool(pThreadPool_t pPool, int thread_num)
{
    pPool->_thread_num = thread_num;
    pPool->_pthid = (pthread_t*)calloc(thread_num, sizeof(pthread_t));
    init_TaskQueue(&pPool->_que);
    return 0;
}

//启动线程池
int boot_ThreadPool(pThreadPool_t pPool)
{
    for (int i = 0; i < pPool->_thread_num; ++i) {
        pthread_create(pPool->_pthid + i, NULL, child_handle, &pPool->_que);
    }
    return 0;
}

//关闭线程池
int close_ThreadPool(pThreadPool_t pPool) 
{
    for (int i = 0; i < pPool->_thread_num; ++i) {
        pthread_join(pPool->_pthid[i], NULL);
    }
    return 0;
}

//销毁线程池资源
int destory_ThreadPool(pThreadPool_t pPool)
{
    for (int i = 0; i < pPool->_thread_num; ++i) {
        free(pPool->_pthid + i);
    }
    return 0;
}
