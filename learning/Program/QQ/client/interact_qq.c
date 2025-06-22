#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;} }


//与聊天室服务器交互
int interact_qq(int sfd)
{
    //定义一个读操作集合
    fd_set rdset;
    FD_ZERO(&rdset);

    char buf[128] = {0};//读写缓冲区
    int ret = -1;
    while (1) {
        //每次select前，重置读集合，因为select会修改读集合（将未就绪的文件描述符置为0）
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);

        //select阻塞在此，等待集合中任意一个文件描述符就绪后，解除阻塞
        //select接触阻塞后，找就绪的文件描述符，需要遍历集合去找
        ret = select(sfd + 1, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        //服务端套接字就绪，表示服务端有数据到来，接收并打印在终端
        if (FD_ISSET(sfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recv(sfd, buf, sizeof(buf) - 1, 0);
            if (0 == ret) {
                //服务端已关闭
                printf("server exit\n");            
                return -1;
            }
            printf("%s\n", buf);
        }

        //标准输入就绪，接收并发送给服务端
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
            send(sfd, buf, strlen(buf) - 1, 0);
        }
    }
}

