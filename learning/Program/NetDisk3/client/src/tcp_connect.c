#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>

//连接服务器
int tcp_connect(char *ip, int port)
{
    int fd_server = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(port);

    if (-1 == connect(fd_server, (struct sockaddr*)&serAddr, sizeof(serAddr))) {
        perror("connect");
        return -1;
    }
    
    return fd_server;
}
