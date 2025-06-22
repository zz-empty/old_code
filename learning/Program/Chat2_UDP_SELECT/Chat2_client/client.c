#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

//检查命令行参数个数                                                                                                                                   
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Args error!\n"); return -1; }}

//检查函数返回值是否合法，非法报错退出
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror("msg");  return -1;  } }


//与服务端交互
//输入：服务器套接字，服务器信息的结构体
int interact_ser(int sfd, struct sockaddr_in *serAddr)
{
    //定义一个都是读操作的文件描述符的集合
    fd_set rdset;
    FD_ZERO(&rdset);

    char buf[128] = {0};//读写缓冲区
    int ret = -1;
    socklen_t serLen = sizeof(struct sockaddr_in);//服务器信息结构体的长度

    //使用select监听所有读操作
    while (1) {
        //重置读集合，因为每次select会修改读集合(将没就绪的文件描述符置为0)
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);

        ret = select(sfd + 1, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        //先给服务端发送数据，建立udp通信，再从服务端接受数据

        //标准输入就绪，读取并发送给服务端
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            sendto(sfd, buf, strlen(buf) - 1, 0, (struct sockaddr*)serAddr, serLen);
        }

        //服务器套接字就绪，读取并打印在终端
        if (FD_ISSET(sfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recvfrom(sfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)serAddr, &serLen);
            if (0 == ret) {
                //服务端已关闭
                printf("server exit\n");            
                return -1;
            }
            printf("ser: %s\n", buf);
        }
    }
}

int main(int argc, char *argv[])
{
    //参数：服务器的ip和端口
    ARGS_CHECK(argc, 3);

    //创建一个udp类型的套接字, 用于与服务端通信
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sfd, -1, "cli_socket");

    //创建存储服务器ip和port的结构体
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serAddr.sin_port = htons(atoi(argv[2]));


    //与服务器交互
    interact_ser(sfd, &serAddr);


    //关闭套接字，断开与服务器的连接
    close(sfd);
    /* printf("Connection closed!\n"); */
    return 0;
}
