#include "../include/qq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Args error!\n");\
    return -1;} }

//与聊天室服务器交互
int interact_qq(int sfd);

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 2);
    //从配置文件中，取出服务器的ip和port
    FILE *fp = fopen(argv[1], "r");
    char ip[128] = {0};
    int port = 0;
    fscanf(fp, "%s%d", ip, &port);
    fclose(fp);

    //连接聊天室服务器
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(port);

    int ret = connect(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "connect");

    //发送用户名
    char username[30] = {0};
    printf("准备进入聊天室，请输入用户名：");
    scanf("%s", username);
    send(sfd, username, strlen(username), 0);
    //清空界面
    system("clear");

    //与聊天室交互
    interact_qq(sfd);

    //关闭服务器套接字
    close(sfd);
    return 0;
}

