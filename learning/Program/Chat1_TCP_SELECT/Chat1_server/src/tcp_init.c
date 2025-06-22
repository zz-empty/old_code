#include "../include/tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

//输入：配置文件(服务器的ip地址，端口号)
//输出：绑定了服务器ip和端口的，正在监听的套接字
int tcp_init(char *conf)
{
    //从配置文件中读取服务器的ip和端口
    FILE* fp = fopen(conf, "r"); 
    char ip[128] = {0};
    char port[128] = {0};
    fscanf(fp, "%s%s", ip, port);
    printf("ip = %s, port = %s\n", ip, port);
    fclose(fp);
    
    //生成一个tcp类型的套接字
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "ser_socket");

    //将套接口设置为可重用, 不用再等待重启时的TIME_WAIT时间
    int reuse = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    //给套接字绑定服务端ip和port
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(atoi(port));

    int ret = bind(sfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "ser_bind");

    //将套接字设为监听模式，并指定最大监听数（全连接队列的大小）
    ret = listen(sfd, 10); 
    ERROR_CHECK(ret, -1, "ser_listen");

    return sfd;
}
