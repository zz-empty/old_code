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


//输入：服务端的ip，和port
//输出：连接到服务端的套接字
int tcp_connect(char *ip, char *port)
{
    //创建一个tcp类型的套接字
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "cli_socket");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(atoi(port));

    //用套接字连接服务器
    int ret = connect(sfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");

    return sfd;
}

//与服务端交互
int interact_sfd(int sfd)
{
    fd_set rdset;
    FD_ZERO(&rdset);

    char buf[128] = {0};
    int ret = -1;
    while (1) {
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);

        ret = select(sfd + 1, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        if (FD_ISSET(sfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recv(sfd, buf, sizeof(buf) - 1, 0);
            if (0 == ret) {
                //服务端已关闭
                printf("server exit\n");            
                return -1;
            }
            printf("ser: %s\n", buf);
        }

        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            send(sfd, buf, strlen(buf) - 1, 0);
        }
    }
}

int main(int argc, char *argv[])
{
    //参数：服务器的ip和端口
    ARGS_CHECK(argc, 3);

    //得到一个可以与服务端通信的套接字
    int sfd = tcp_connect(argv[1], argv[2]);
    printf("Already connect the server(ip: %s, port: %s)\n", argv[1], argv[2]);

#if 0
    //给服务器发信息
    char buf[128] = {0};
    stpcpy(buf, "OKKKKKK! connect, this is blue space!");
    send(sfd, buf, strlen(buf), 0);

    //从服务器收消息
    memset(buf, 0, sizeof(buf));
    recv(sfd, buf, sizeof(buf) - 1, 0);
    puts(buf);
#endif

    interact_sfd(sfd);

    //关闭套接字，断开与服务器的连接
    close(sfd);
    /* printf("Connection closed!\n"); */
    return 0;
}
