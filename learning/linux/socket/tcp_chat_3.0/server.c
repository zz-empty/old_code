#include "tcp.h"


int main(int argc, char *argv[]) 
{
    //ip port
    ARGS_CHECK(argc, 3);
    printf("server pid = %d\n", getpid());

    //create socket
    int sfd = tcpInit(argv[1], argv[2]);

    int cfd = 0;
    char buf[64] = {0};
    int ret = 0;

    //select fds
    fd_set rdset;
    FD_ZERO(&rdset);
    fd_set needMonitorSet;
    FD_ZERO(&needMonitorSet);
    FD_SET(sfd, &needMonitorSet);
    FD_SET(STDIN_FILENO, &needMonitorSet);

    while (1) {
        memcpy(&rdset, &needMonitorSet, sizeof(fd_set));
        ret = select(10, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        if (FD_ISSET(sfd, &rdset)) {
            //tcp established with client
            /* cfd = tcpAccept(sfd); */
            cfd = accept(sfd, NULL, NULL);
            printf("client connect\n");
            FD_SET(cfd, &needMonitorSet);
        }

        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            send(cfd, buf, strlen(buf) - 1, 0);
        }

        if (FD_ISSET(cfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recv(cfd, buf, sizeof(buf) - 1, 0);
            if (0 == ret) {
                printf("client exit\n");
                close(cfd);
                FD_CLR(cfd, &needMonitorSet);
                continue;
            }
            printf("buf = %s\n", buf);
        }
    }

    close(sfd);
    return 0;
}

int tcpInit(char *ip, char *port) {
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
