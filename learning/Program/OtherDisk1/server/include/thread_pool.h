#ifndef __THREAD_POOL__
#define __THREAD_POOL__
#include "head.h"
#include "work_que.h"

typedef void * (* thread_func_t)(void *);
//线程池的数据结构
typedef struct{
    int start_flag;//默认0，线程池未启动，为1，表示线程池启动了
    int pthread_num;//线程的数目
    Que_t que;//队列
    pthread_t *pthid;//指向线程pthread_id的起始地址
    thread_func_t download_thread;//下载线程的入口函数
}Thread_pool_t,*pThread_pool;

int thread_pool_init(pThread_pool pPool,int thread_num);
void * thread_func(void *p);
int thread_pool_start(pThread_pool pPool);

int tcp_init(char *ip,char *port,int *fd);//封装socket、bind和listen，返回sfd
int epoll_add(int epfd,int fd);
int epoll_del(int epfd,int fd);
int trans_file(int new_fd);

#endif
