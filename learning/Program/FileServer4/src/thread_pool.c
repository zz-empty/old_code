#include "../include/head.h"
#include "../include/thread_pool.h"
#include "../include/task_queue.h"

//线程清理函数
void clean_func(void *p)
{
    pTaskQueue_t pQue = (pTaskQueue_t)p;
    pthread_mutex_unlock(&pQue->_mutex);
}

//线程函数
void *thread_func(void *p)
{
    //拿到任务队列地址
    pTaskQueue_t pQue = (pTaskQueue_t)p;

    pTaskNode_t pCur = NULL;
    while (1) {
        //如果队列中的退出标志置位，退出线程
        if (1 == pQue->_flag) {
            printf("thread exit!\n");
            pthread_exit(NULL);
        }

        //取任务
        pthread_mutex_lock(&pQue->_mutex);
        pthread_cleanup_push(clean_func, pQue);

        if (0 == pQue->_size) {
            pthread_cond_wait(&pQue->_cond, &pQue->_mutex);
        }
        int ret = get_TaskNode(pQue, &pCur);

        pthread_mutex_unlock(&pQue->_mutex);

        //执行任务，发送文件
        if (-1 != ret) {
            char filename[128] = "file";
            send_file_truck(pCur->_clifd, filename); 
            printf("----------------------------send finish!\n");
            //任务完成，销毁任务节点
            free(pCur);
            pCur = NULL;
        }

        pthread_cleanup_pop(1);
    }

}

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
    printf("thread_num: %d\n", pPool->_thread_num);
    for (int i = 0; i < pPool->_thread_num; ++i) {
        pthread_create(&pPool->_pthid[i], NULL, thread_func, &pPool->_que);
    }
    return 0;
}
