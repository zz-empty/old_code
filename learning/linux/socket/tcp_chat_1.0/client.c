#include "tcp.h"

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);

    int sfd = tcpConnect(argv[1], argv[2]);

    //send msg to sfd
    send(sfd, "helloserver", 11, 0);

    //receive msg from sfd
    char buf[64] = {0};
    recv(sfd, buf, sizeof(buf) - 1, 0);
    printf("buf = %s\n", buf);
    return 0;
}

int tcpConnect(char *ip, char *port) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(atoi(port));

    int ret = 0;
    ret = connect(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_AND_CLOSE(ret, -1, "connect", sfd);

    return sfd;
}
