#include "../include/tcp.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //命令行参数：配置文件
    ARGS_CHECK(argc, 2);

    //生成一个服务器套接字, 并监听客户端的连接
    int sfd = tcp_init(argv[1]);
    if (-1 == sfd) {
        return -1;
    }
    printf("The server is listening...\n");


    //与客户端进行信息交互
    interact_cli(sfd);


    //关闭服务器套接字
    close(sfd);
    printf("The server is closed!\n");
    return 0;
}
