#include "../include/tcp.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //命令行参数：配置文件
    ARGS_CHECK(argc, 2);

    //得到一个已绑定服务器ip和port的，正在监听的，tcp类型套接字
    int sfd = tcp_init(argv[1]);
    printf("The server is listening...\n");

    //与客户端交互，用epoll管理所有文件描述符
    if (-1 != sfd) {
        interact_cli(sfd);
    }

    //关闭服务器套接字
    close(sfd);
    printf("The server is closed!\n");
    return 0;
}
