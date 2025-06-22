#include "../include/udp.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    //命令行参数：配置文件路径
    ARGS_CHECK(argc, 2);

    //得到一个绑定了服务器ip和端口的udp类型的套接字
    int sfd = udp_init(argv[1]);

    //与客户端交互
    interact_cli(sfd); 

    //关闭服务器套接字
    close(sfd);
    return 0;
}
