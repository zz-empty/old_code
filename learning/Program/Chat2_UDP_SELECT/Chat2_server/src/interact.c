#include "../include/udp.h"
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//接受所有客户端的信息，并显示在终端
//只能发消息给最后一个连接的客户端
int interact_cli(int sfd)
{
    //定义客户端结构体，用来接受客户端的ip和port
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t cliLen = sizeof(clientAddr);

    int ret = 0;
    char buf[64] = {0};//读写缓冲区

    //需要先接收客户端信息,建立udp通信
    //同时获取客户端的ip和port
    ret = recvfrom(sfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&clientAddr, &cliLen);
    ERROR_CHECK(ret, -1, "recvfrom");
    printf("cli: %s\n", buf);

    //定义一个都是读操作的文件描述符的集合
    fd_set rdset;
    FD_ZERO(&rdset);

    //使用select监听所有读操作
    while (1) {
        //重置读集合，因为每次select会修改读集合(将没就绪的文件描述符置为0)
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);

        ret = select(10, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        //服务器套接字就绪，有客户端的数据，读取并打印在终端
        if (FD_ISSET(sfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recvfrom(sfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&clientAddr, &cliLen);
            ERROR_CHECK(ret, -1, "recvfrom");
            if (0 == ret) {
                printf("client exit!\n");
                continue;
            }
            printf("cli: %s\n", buf);

            //可以同时回复客户端一些信息
            //sendto
        }

        //标准输入就绪，读取并发送给最后一个连接的客户端
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            sendto(sfd, buf, strlen(buf) - 1, 0, (struct sockaddr*)&clientAddr, cliLen);
        }
    }

    return 0;
}
