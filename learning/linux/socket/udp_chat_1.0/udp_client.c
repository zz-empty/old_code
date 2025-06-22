#include "udp.h"

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);

    //生成一个套接字，用来udp通信
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serAddr.sin_port = htons(atoi(argv[2]));
    socklen_t serLen = sizeof(serAddr);

    char buf[64] = {0};
    int ret;

    ret = sendto(sfd, "helloserver", 11, 0, (struct sockaddr*)&serAddr, serLen);
    ERROR_AND_CLOSE(ret, -1, "sendto", sfd);

    ret = recvfrom(sfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&serAddr, &serLen);
    ERROR_AND_CLOSE(ret, -1, "recvfrom", sfd);
    printf("buf = %s\n", buf);

    close(sfd);
    return 0;
}

