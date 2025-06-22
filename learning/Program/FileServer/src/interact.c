#include "../include/process_pool.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include <sys/socket.h>
#include <sys/epoll.h>

int epollAddFd(int fd, int epfd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    return 0;
}


//功能：服务器主进程处理来自客户端和进程池的请求,以及退出信号
//参数：服务器套接字，子进程数组，子进程数量, 退出管道读端
int interact_cli(int sfd, pProcInfo_t pChilds, int childsNum, int exitpipe)
{
    //接受所有客户端的连接，将客户端套接字转发给空闲子进程处理
    //将工作完的子进程状态设为空闲
    //收到退出信号，实现进程池的退出
    

#if 0
    //使用epoll管理所有文件描述符
    int epfd = epoll_create(1);

    //将sfd添加进epfd
    epollAddFd(sfd, epfd);

    //将子进程的管道fd，加入epfd
    int i = 0;
    for (i = 0; i < childsNum; ++i) {
        epollAddFd(pChilds[i]._pipefd, epfd);
    }

    //将接收退出信号的管道加入epfd
    epollAddFd(exitpipe, epfd);

    int readyFdNum = 0;//就绪的文件描述符数量
    struct epoll_event evs[2]; //epoll_wait等待数组的大小
    int newfd = 0;//客户端的套接字
#endif

    int epfd = epoll_create(1);
    //add sfd to epoll
    epollAddFd(sfd, epfd);
    //add child_fd to epoll
    int i = 0;
    for (i = 0; i < childsNum; ++i) {
        epollAddFd(pChilds[i]._pipefd, epfd);
    }
    //add exitpipe to epoll
    epollAddFd(exitpipe, epfd);

    //4.listen client require
    int readyFdNum = 0;
    struct epoll_event evs[2];//用于接收准备就绪的事件
    memset(evs, 0, sizeof(evs));
    int newfd = 0;
    //epoll等待就绪的文件描述符
    while (1) {
        readyFdNum = epoll_wait(epfd, evs, 2, -1);
        /* ERROR_CHECK(readyFdNum, -1, "epoll_wait"); */
        //这里不能检查epoll_wait的返回值
        //epoll_wait等待时可能会收到终止信号，这将导致调用被中断

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
                        sendFd(pChilds[j]._pipefd, newfd);
                        pChilds[j]._flag = 1;   //将子进程状态设为忙碌
                        printf("the child_pid %d is working...\n", pChilds[j]._pid);
                        break;
                    }
                }

                //任务已传给空闲子进程，关掉客户端套接字
                //主进程只管调度任务，不管具体实现
                close(newfd);
            }
            
            else if (evs[i].data.fd == exitpipe) {
                int j = 0;
                //let child_process exit
                for (j = 0; j < childsNum; ++j) {
                    kill(pChilds[j]._pid, SIGUSR1);
                }

                //Recycling child_resources
                for (j = 0; j < childsNum; ++j) {
                    wait(NULL);
                }

                //main_process exit
                printf("main exit!\n");
                exit(0);
            }

#if 0
            //收到退出信号
            else if (evs[i].data.fd == exitpipe) {
                int j;
                //杀掉所有子进程
                for (j = 0; j < childsNum; ++j) {
                    kill(pChilds[j]._pid, SIGUSR1);
                }

                //回收所有子进程资源
                for (j = 0; j < childsNum; ++j) {
                    wait(NULL);
                }

                //服务器退出
                printf("Server exit!\n");
                exit(0);
            }
#endif

            //子进程套接口就绪，将就绪的子进程状态设为空闲
            else  {
		        int j;
                for (j = 0; j < childsNum; ++j) {
                    if (evs[i].data.fd == pChilds[j]._pipefd) {
                        char buf[] = "aaa";
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
