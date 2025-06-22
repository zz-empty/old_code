#include "../include/process_pool.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include <sys/socket.h>
#include <sys/epoll.h>



//功能：服务器主进程处理来自客户端和进程池的请求,以及退出信号
//参数：服务器套接字，子进程数组，子进程数量, 退出管道读端
int interact_cli(int sfd, pProcInfo_t pChilds, int childsNum, int exitpipe)
{
    //接受所有客户端的连接，将客户端套接字转发给空闲子进程处理
    //将工作完的子进程状态设为空闲
    //收到退出信号，实现进程池的退出
    

    //使用epoll管理所有文件描述符
    int epfd = epoll_create(1);

    //定义读事件
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;

    //将sfd添加进epfd
    event.data.fd = sfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);

    //将子进程的管道fd，加入epfd
    int i;
    for (i = 0; i < childsNum; ++i) {
        event.data.fd = pChilds[i]._pipefd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, pChilds[i]._pipefd, &event);
    }

    //将接收退出信号的管道加入epfd
    event.data.fd = exitpipe;
    epoll_ctl(epfd, EPOLL_CTL_ADD, exitpipe, &event);

    char buf[128] = {0};//读写缓冲区
    int readyFdNum = 0;//就绪的文件描述符数量
    struct epoll_event evs[2]; //epoll_wait等待数组的大小
    int newfd = 0;//客户端的套接字

    //epoll等待就绪的文件描述符
    while (1) {
        readyFdNum = epoll_wait(epfd, evs, 2, -1);

        for (i = 0; i < readyFdNum; ++i) {

            //服务端套接字就绪，有新的客户端申请连接，将其发送给空闲子进程
            if (evs[i].data.fd == sfd) {
                //newfd指向最后一个客户端套接字
                //每次accept都会更新newfd
                newfd = accept(sfd, NULL, NULL);

                //将newfd交给空闲子进程
                int j;
                for (j = 0; j < childsNum; ++j) {
                    if (0 == pChilds[j]._flag) {
                        sendFd(pChilds[j]._pipefd, newfd, 0);
                        pChilds[j]._flag = 1;   //将子进程状态设为忙碌
                        printf("the child_pid %d is working...\n", pChilds[j]._pid);
                        break;
                    }
                }

                //任务已传给空闲子进程，关掉客户端套接字
                //主进程只管调度任务，不管具体实现
                close(newfd);
            }

            //收到退出信号
            else if (evs[i].data.fd == exitpipe) {
                int j;
                //通知所有子进程退出,将退出标志位设为1
                for (j = 0; j < childsNum; ++j) {
                    sendFd(pChilds[j]._pipefd, 0, 1);
                }

                //回收所有子进程资源
                for (j = 0; j < childsNum; ++j) {
                    wait(NULL);
                }

                //服务器退出
                printf("Server exit!\n");
                exit(0);
            }

            //子进程套接口就绪，将就绪的子进程状态设为空闲
            else  {
		        int j;
                for (j = 0; j < childsNum; ++j) {
                    if (evs[i].data.fd == pChilds[j]._pipefd) {
                        read(pChilds[j]._pipefd, buf, sizeof(buf) - 1);//读取子进程套接口
                        pChilds[j]._flag = 0;
                        printf("the child_pid %d finished work!\n", pChilds[j]._pid);
                    }
                }
            }
        }
    }
    return 0;
}
