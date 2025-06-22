#include "../include/head.h"
#include "../include/thread_pool.h"
#include "../include/task_queue.h"
#include "../include/type.h"


//线程清理函数
void clean_func(void *p)
{
    pTaskQueue_t pQue = (pTaskQueue_t)p;
    pthread_mutex_unlock(&pQue->_mutex);    //解锁
}

//线程函数
void *thread_func(void *p)
{
    //拿到任务队列地址
    pTaskQueue_t pQue = (pTaskQueue_t)p;

    //用来从队列中获取任务节点
    pTaskNode_t pCur = NULL;
    while (1) {
        //如果队列中的退出标志为1，退出线程
        if (1 == pQue->_flag) {
            printf("thread exit!\n");
            pthread_exit(NULL);
        }

        //取任务，拿到一个客户端fd
        pthread_mutex_lock(&pQue->_mutex);
        pthread_cleanup_push(clean_func, pQue);//注册线程清理函数，防止线程意外终止，导致锁无法释放

        if (0 == pQue->_size) { 
            pthread_cond_wait(&pQue->_cond, &pQue->_mutex);//如果没有任务，睡在条件变量上，等待任务
        }
        int ret = get_TaskNode(pQue, &pCur);    //得到任务

        pthread_mutex_unlock(&pQue->_mutex);

        //执行任务

        //任务完成，销毁任务节点
        free(pCur);
        pCur = NULL;

        pthread_cleanup_pop(1);
    }

}

//初始化线程池
int init_ThreadPool(pThreadPool_t pPool, int thread_num)
{
    pPool->_start_flag = 0;             //初始化为关闭状态
    pPool->_thread_num = thread_num;    //设置线程数量
    pPool->_pthid = (pthread_t*)calloc(thread_num, sizeof(pthread_t));//创建thread_num个子线程
    init_TaskQueue(&pPool->_que);       //初始化任务队列
    pPool->_thread_func = thread_func;  //线程函数
    return 0;
}


//启动线程池
int boot_ThreadPool(pThreadPool_t pPool)
{
    printf("thread_num: %d\n", pPool->_thread_num);

    pPool->_start_flag = 1; //启动线程池
    for (int i = 0; i < pPool->_thread_num; ++i) {  //循环创建线程
        pthread_create(&pPool->_pthid[i], NULL, pPool->_thread_func, &pPool->_que);
    }
    return 0;
}
