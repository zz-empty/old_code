#include "../include/tcp.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/epoll.h>


//接受所有客户端的信息，并显示在终端
//将信息发送给所有客户端
int interact_cli(int sfd)
{
    /* //得到一个客户端套接字，用于通信 */
    /* int cfd = accept(sfd, NULL, NULL); */
    /* ERROR_CHECK(cfd, -1, "accept"); */

    int ret = -1;

    //使用epoll管理所有文件描述符
    int epfd = epoll_create(1);

    //将读事件注册进epfd
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;

    //将标准输入添加进epfd
    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_add_stdin");

    //将sfd添加进epfd
    event.data.fd = sfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
    ERROR_CHECK(ret, -1, "epoll_add_sfd");

    char buf[128] = {0};//读写缓冲区
    int readyFdNum = 0;//就绪的文件描述符数量
    struct epoll_event evs[2]; //epoll_wait等待数组的大小
    int newfd = 0;//客户端的套接字

    //epoll等待就绪的文件描述符
    while (1) {
        readyFdNum = epoll_wait(epfd, evs, 2, -1);
        ERROR_CHECK(readyFdNum, -1, "epoll_wait");

        for (int i = 0; i < readyFdNum; ++i) {
            //标准输入就绪，发消息给客户端
            if (evs[i].data.fd == STDIN_FILENO) {
                memset(buf, 0, sizeof(buf));
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
                ERROR_CHECK(ret, -1, "read");

                /* //给最后一个连接的客户端发消息 */
                /* send(newfd, buf, strlen(buf) - 1, 0); */

                //群发消息给客户端
                //最小的客户端套接字是4
                //0-标准输入，1-标准输出，2-标准错误输出，3-sfd
                for (int i = 4; i <= newfd; ++i) {
                    send(i, buf, strlen(buf) - 1, 0);
                }
            }

            //服务端套接字就绪，有新的客户端申请连接
            //将其加入进epfd
            else if (evs[i].data.fd == sfd) {
                //newfd指向最后一个客户端套接字
                //每次accept都会更新newfd
                newfd = accept(sfd, NULL, NULL);

                //默认的客户端套接字是水平触发（LT模式）
                //可修改为边缘触发（ET模式），更高效，适用于高并发场景
                /* event.events = EPOLLIN | EPOLLET; */
                event.data.fd = newfd;

                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, newfd, &event);
                ERROR_CHECK(ret, -1, "epoll_add_newfd");
            }

            //客户端套接字就绪，读取并打印在终端
            else  {
#if 0
                //客户端套接字为边缘触发模式时，一次性接受全部信息
                while (1) {
                    memset(buf, 0, sizeof(buf));
                    //接受信息，如果收不到信息，表示客户端断开
                    //recv非阻塞版，将flag设为MSG_DONTWAIT
                    ret = recv(evs[i].data.fd, buf, sizeof(buf) - 1, MSG_DONTWAIT);
                    if (0 == ret) {
                        //对端已断开, 退出监听
                        printf("client exit!\n");
                        close(evs[i].data.fd);
                        return 0;
                    }
                    else if (-1 == ret) {
                        //接收不到数据时，退出
                        break;
                    }
                    //将信息输出在终端
                    printf("cli: %s\n", buf);
                }            
#else
                //客户端套接字为水平触发模式
                memset(buf, 0, sizeof(buf));
                //接受信息，如果收不到信息，表示客户端断开
                ret = recv(evs[i].data.fd, buf, sizeof(buf) - 1, 0);
                ERROR_CHECK(ret, -1, "recv");
                if (0 == ret) {
                    //对端已断开, 退出监听
                    printf("client exit!\n");
                    close(evs[i].data.fd);
                    return 0;
                }
                //将信息输出在终端
                printf("cli: %s\n", buf);
#endif
            }
        }
    }
    return 0;
}
