#include "udp.h"

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);
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

    //select stdin sfd
    fd_set rdset;
    FD_ZERO(&rdset);
    while (1) {
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);
        ret = select(sfd + 1, &rdset, NULL, NULL, NULL);
        ERROR_AND_CLOSE(ret, -1, "select", sfd);

        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            ret = sendto(sfd, buf, strlen(buf) - 1, 0, (struct sockaddr*)&serAddr, serLen);
            ERROR_AND_CLOSE(ret, -1, "sendto", sfd);
        }
        if (FD_ISSET(sfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recvfrom(sfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&serAddr, &serLen);
            ERROR_AND_CLOSE(ret, -1, "recvfrom", sfd);
            printf("buf = %s\n", buf);
        }
    }


    close(sfd);
    return 0;
}

