#include "tcp.h"

int main(int argc, char *argv[]) 
{
    //ip port
    ARGS_CHECK(argc, 3);

    int sfd = tcpInit(argv[1], argv[2]);
    int cfd = tcpAccept(sfd);

    //reveive msg
    char buf[64] = {0};
    recv(cfd, buf, sizeof(buf) - 1, 0);
    printf("buf = %s\n", buf);

    //send msg
    send(cfd, "helloclient", 11, 0);

    close(sfd);
    close(cfd);
    return 0;
}

int tcpInit(char *ip, char *port) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(struct sockaddr_in));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(atoi(port));

    int ret;
    ret = bind(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_AND_CLOSE(ret, -1, "bind", sfd);

    ret = listen(sfd, 10);
    ERROR_AND_CLOSE(ret, -1, "listen", sfd);
    return sfd;
}

int tcpAccept(int sfd) {
    struct sockaddr_in cliAddr;
    /* memset(&cliAddr, 0, sizeof(cliAddr)); */
    socklen_t cliLen;

    int cfd = accept(sfd, (struct sockaddr*)&cliAddr, &cliLen);
    ERROR_AND_CLOSE(cfd, -1, "accept", sfd);

    printf("%s %d success connect...\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
    return cfd;
}
