#include "udp.h"

int main(int argc, char *argv[]) 
{
    //ip port
    ARGS_CHECK(argc, 3);
    //生成一个套接字，绑定本地的ip和端口
    int sfd = tcpInit(argv[1], argv[2]);

    struct sockaddr_in cliAddr;
    memset(&cliAddr, 0, sizeof(cliAddr));
    socklen_t cliLen = sizeof(cliAddr);
    
    int ret = 0;
    char buf[64] = {0};

    ret = recvfrom(sfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&cliAddr, &cliLen);
    ERROR_AND_CLOSE(ret, -1, "recvfrom", sfd);
    printf("buf = %s\n", buf);

    ret = sendto(sfd, "helloclient", 11, 0, (struct sockaddr*)&cliAddr, cliLen);
    ERROR_AND_CLOSE(ret, -1, "sendto", sfd);

    close(sfd);
    return 0;
}

int tcpInit(char *ip, char *port) {
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(atoi(port));

    int ret;
    ret = bind(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_AND_CLOSE(ret, -1, "bind", sfd); 
    return sfd;
}
