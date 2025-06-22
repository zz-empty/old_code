#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "head.h"
#include "task_queue.h"

typedef void *(*Func_t)(void*);
//线程池
typedef struct {
    char _start_flag;   //启动标志 0-未启动 1-启动
    int _thread_num; //子线程数量
    pthread_t *_pthid;  //子线程数组
    TaskQueue_t _que;   //任务队列
    Func_t _thread_func;  //线程工作函数, 参数是任务队列的地址
}ThreadPool_t, *pThreadPool_t;

//初始化线程池
int init_ThreadPool(pThreadPool_t pPool, int thread_num);

//启动线程池
int boot_ThreadPool(pThreadPool_t pPool);

//创建一个tcp类型，正在监听的服务器套接字
int tcp_init(char *ip, int port);

//功能：服务器主线程，将新连接的客户端加入线程池中的任务队列，然后通知子线程处理
int interact_cli(int sfd, int exitpipe, pThreadPool_t pPool);

//使用私有协议传输数据，给另一个进程传输文件
int send_file_truck(int socket_fd, char *filename);

//将fd加入epfd
int epoll_add(int fd, int epfd);

//将fd从epfd中移除
int epoll_del(int fd, int epfd);

#endif
