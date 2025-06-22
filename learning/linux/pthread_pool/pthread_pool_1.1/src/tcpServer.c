#include "../include/head.h"

int tcpInit(char *ip, char *port, int *sockFd) 
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");
    //port can reuse
    int reuse = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(struct sockaddr_in));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(atoi(port));

    int ret;
    ret = bind(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(sfd, 10);
    ERROR_CHECK(ret, -1, "listen");

    *sockFd = sfd;
    return sfd;
}

int tcpAccept(int sfd) {
    struct sockaddr_in cliAddr;
    /* memset(&cliAddr, 0, sizeof(cliAddr)); */
    socklen_t cliLen;

    int cfd = accept(sfd, (struct sockaddr*)&cliAddr, &cliLen);
    ERROR_CHECK(cfd, -1, "accept");

    printf("%s %d success connect...\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
    return cfd;
}
