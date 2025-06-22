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

//初始化线程池
int init_ThreadPool(pThreadPool_t pPool, int thread_num);

//启动线程池
int boot_ThreadPool(pThreadPool_t pPool);

//功能：服务器主线程，将新连接的客户端加入线程池中的任务队列，然后通知子线程处理
int interact_cli(int sfd, pThreadPool_t pPool, int exitpipe);

//使用私有协议传输数据，给另一个进程传输文件
int send_file_truck(int socket_fd, char *filename);

#endif
