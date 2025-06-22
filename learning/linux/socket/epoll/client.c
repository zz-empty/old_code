#include "tcp.h"

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);
    //connect to server
    int sfd = tcpConnect(argv[1], argv[2]);

    char buf[64] = {0};
    int ret = 0;

    fd_set rdset;
    FD_ZERO(&rdset);
    while (1) {
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sfd, &rdset);
        ret = select(sfd + 1, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            send(sfd, buf, strlen(buf) - 1, 0);
        }
        
        if (FD_ISSET(sfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recv(sfd, buf, sizeof(buf) - 1, 0);
            if (0 == ret) {
                printf("server exit\n");
                break;
            }
            printf("buf = %s\n", buf);
        }
    }

    close(sfd);
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
