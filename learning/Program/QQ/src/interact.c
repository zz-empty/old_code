#include "../include/qq.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>

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

//用fd查找用户
pUsr_t search_usr(pUsr_t pArr, int len, int fd)
{
    int i;
    for (i = 0; i < len; ++i) {
        if (fd == pArr[i]._usrfd) {
            return pArr + i;
        }
    }
    return NULL;
}


//功能：服务器主进程处理来自用户的连接，发信息，退出
//参数：服务器套接字，用户数组，用户最大容量
int interact_usr(int sfd, pUsr_t pUsrArr, int max_capacity)
{
    //使用epoll管理所有文件描述符
    int epfd = epoll_create(1);

    //将sfd添加进epfd
    epollAddFd(sfd, epfd);

    int ret = -1;
    char buf[256] = {0};//读写缓冲区
    int readyFdNum = 0;//就绪的文件描述符数量
    struct epoll_event evs[2]; //epoll_wait等待数组的大小
    int newfd = 0;//客户端的套接字
    int cur_count = 0; //当前在线用户数量

    //epoll等待就绪的文件描述符
    while (1) {
        readyFdNum = epoll_wait(epfd, evs, 2, -1);

        int i;
        for (i = 0; i < readyFdNum; ++i) {

            //服务端套接字就绪，有新用户连接
            if (evs[i].data.fd == sfd) {
                //接收用户端
                newfd = accept(sfd, NULL, NULL);

                //如果用户数组已满，不再接收新用户的连接
                if (cur_count == max_capacity) {
                    strcpy(buf, "网络聊天室人数已满，无法加入");
                    send(newfd, buf, strlen(buf), 0);
                    close(newfd);
                    continue;
                }

                //接收用户名
                memset(buf, 0, sizeof(buf));
                recv(newfd, buf, sizeof(buf) - 1, 0);
                //放入用户数组
                int j;
                for (j = 0; j < max_capacity; ++j) {
                    if (0 == pUsrArr[j]._online) {
                        pUsrArr[j]._usrfd = newfd;//记录用户通信fd
                        pUsrArr[j]._online = 1;//新用户状态更新成在线
                        strcpy(pUsrArr[j]._usrname, buf);//设置用户名

                        //将新用户加入epoll监听
                        epollAddFd(pUsrArr[j]._usrfd, epfd);
                        //给新用户发送欢迎信息
                        strcpy(buf, "===========================Welcome to the best Online Chat Romm==========================\n\n");
                        send(newfd, buf, strlen(buf), 0);

                        //通知其他在线用户，有新用户加入
                        memset(buf, 0, sizeof(buf));
                        sprintf(buf, "==[new user %s join!]==", pUsrArr[j]._usrname);
                        for (int k = 0; k < max_capacity; ++k) {
                            if (pUsrArr[k]._online && pUsrArr[k]._usrfd != pUsrArr[j]._usrfd) {
                                send(pUsrArr[k]._usrfd, buf, strlen(buf), 0);
                            }
                        }

                        break;
                    }
                }
                ++cur_count;//用户记录器++
                printf("cur_count : %d\n", cur_count);
            }

            //用户端发来消息
            else {
                //接收消息
                memset(buf, 0, sizeof(buf));
                ret = recv(evs[i].data.fd, buf, sizeof(buf) - 1, 0);

                //定位发消息的用户
                pUsr_t pCur = search_usr(pUsrArr, max_capacity, evs[i].data.fd);
                //如果用户退出
                if (0 == ret) {
                    --cur_count;//用户记录器--
                    pCur->_online = 0;//用户下线

                    sprintf(buf, "==[usr_%s exit!]==",pCur->_usrname);
                    puts(buf);
                    printf("cur_count : %d\n", cur_count);

                    //从epoll管理的红黑树中删除
                    epollDelFd(pCur->_usrfd, epfd);
                    //通知其他用户
                    for (int j = 0; j < max_capacity; ++j) {
                        if (pUsrArr[j]._online && pCur->_usrfd != pUsrArr[j]._usrfd) {
                            send(pUsrArr[j]._usrfd, buf, strlen(buf), 0);
                        }
                    }
                }
                //正常消息，进行转发给其他在线用户
                else {
                    char usr_info[1024] = {0};
                    sprintf(usr_info, "[%s]: %s", pCur->_usrname, buf);

                    for (int j = 0; j < max_capacity; ++j) {
                        if (pUsrArr[j]._usrfd != pCur->_usrfd && pUsrArr[j]._online) {
                            send(pUsrArr[j]._usrfd, usr_info, strlen(usr_info), 0);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
