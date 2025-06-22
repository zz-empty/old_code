#include "../include/qq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//检查命令行参数个数
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Args error!\n");\
    return -1;  }}

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    //从配置文件中取出服务器ip、port、最多的在线用户数
    FILE *fp = fopen(argv[1], "r");
    char ip[128] = {0};
    int port = 0;
    int max_capacity = 0;
    fscanf(fp, "%s%d%d", ip, &port, &max_capacity);
    fclose(fp);

    //创建用户数组，存储用户信息
    pUsr_t pUsrArr = (pUsr_t)calloc(max_capacity, sizeof(Usr_t));    

    //建立一个正在监听的tcp类型的服务器套接字
    int sfd = tcp_init(ip, port);
    printf("qq_server boot...\n");
    printf("max_capacity : %d\n", max_capacity);

    //处理用户端请求
    interact_usr(sfd, pUsrArr, max_capacity);

    //关闭服务器套接字
    close(sfd);
    printf("qq_server was closed!\n");
    //释放用户数组
    free(pUsrArr);
    pUsrArr = NULL;
    return 0;
}
