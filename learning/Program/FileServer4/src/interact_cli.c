#include "../include/head.h"
#include "../include/task_queue.h"
#include "../include/thread_pool.h"

//将fd加入epfd
int epollAddFd(int fd, int epfd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    ERROR_CHECK(ret, -1, "EPOLL_CTL_ADD");
    return 0;
}

//将fd从epfd中移除
int epollDelFd(int fd, int epfd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
    ERROR_CHECK(ret, -1, "EPOLL_CTL_DEL");
    return 0;
}



//功能：服务器主线程，将新连接的用户加入线程池中的任务队列，然后通知子线程处理
//参数：服务器套接字，线程池地址，退出管道
int interact_cli(int sfd, pThreadPool_t pPool, int exitpipe)
{
    //使用epoll管理所有文件描述符
    int epfd = epoll_create(1);

    //将sfd添加进epfd
    epollAddFd(sfd, epfd);
    //将用来退出的管道加入epfd
    epollAddFd(exitpipe, epfd);

    int readyFdNum = 0;//就绪的文件描述符数量
    struct epoll_event evs[2]; //epoll_wait等待数组的大小
    int newfd = 0;//客户端的套接字

    //epoll等待就绪的文件描述符
    while (1) {
        readyFdNum = epoll_wait(epfd, evs, 2, -1);

        int i;
        for (i = 0; i < readyFdNum; ++i) {

            //服务端套接字就绪，有新用户连接
            if (evs[i].data.fd == sfd) {
                //接收用户端
                newfd = accept(sfd, NULL, NULL);

                //新建任务节点
                pTaskNode_t pNew = (pTaskNode_t)calloc(1, sizeof(TaskNode_t));
                pNew->_clifd = newfd;

                pthread_mutex_lock(&pPool->_que._mutex);//加锁

                push_TaskQueue(&pPool->_que, pNew); //将新节点放入任务队列
                pthread_cond_signal(&pPool->_que._cond);//通知子线程

                pthread_mutex_unlock(&pPool->_que._mutex);//解锁
            }

            //退出管道就绪，通知线程池退出
            if (evs[i].data.fd == exitpipe) {
                //将退出标志位设为1
                pPool->_que._flag = 1;
                //唤醒所有线程池内的线程
                pthread_cond_broadcast(&pPool->_que._cond);

                //回收线程池的资源
                for (int j = 0; j < pPool->_thread_num; ++j) {
                    pthread_join(pPool->_pthid[j], NULL);
                }

                //退出子进程
                exit(0);
            }
        }
    }

    return 0;
}
