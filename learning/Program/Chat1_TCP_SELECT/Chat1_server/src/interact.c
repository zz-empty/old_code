#include "../include/tcp.h"
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//接受所有客户端的信息，并显示在终端
//将信息发送给所有客户端
int interact_cli(int sfd)
{
    //用select监听sfd, 标准输入，和客户端
    fd_set monitor_set;//位图，存放所有被监听的文件描述符
    FD_ZERO(&monitor_set);
    FD_SET(STDIN_FILENO, &monitor_set);
    FD_SET(sfd, &monitor_set);

    int readyFdNum = 0;//就绪的文件描述符数量
    char buf[128] = {0};//读写缓冲区
    int ret = -1;
    int client_fd = 0;

    fd_set rdset;//本轮读操作位图
    while (1) {
        //当前的client_fd是最大的客户端套接字
        memcpy(&rdset, &monitor_set, sizeof(fd_set));

        //读操作位图中，没有就绪的文件描述符会被select修改为0
        readyFdNum = select(10, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(readyFdNum, -1, "select");

        //如果sfd就绪，表示有新的客户端请求连接, 将其加入监听集合
        if (FD_ISSET(sfd, &rdset)) {
            //得到一个客户端套接字，用于通信
            client_fd = accept(sfd, NULL, NULL);
            ERROR_CHECK(client_fd, -1, "accept");
            FD_SET(client_fd, &monitor_set);
        }

        //标准输入就绪，读取并发送给客户端
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
            ERROR_CHECK(ret, -1, "read");

            //将信息发给所有客户端
            for (int i = 4; i <= client_fd; ++i) {
                send(i, buf, strlen(buf) - 1, 0);
            }
        }

        //遍历所有客户端，哪个客户端就绪，读取并显示在终端
        for (int cli_fd = 4; cli_fd < 10; ++cli_fd) {
            if (FD_ISSET(cli_fd, &rdset)) {
                memset(buf, 0, sizeof(buf));
                //接受信息，如果收不到信息，表示客户端断开
                ret = recv(cli_fd, buf, sizeof(buf) - 1, 0);
                ERROR_CHECK(ret, -1, "recv");
                if (0 == ret) {
                    //对端已断开, 退出监听
                    printf("client exit!\n");
                    close(cli_fd);
                    FD_CLR(cli_fd, &monitor_set);
                    continue;
                }
                //将信息输出在终端
                printf("cli: %s\n", buf);
            }
        }
    }

    return 0;
}
