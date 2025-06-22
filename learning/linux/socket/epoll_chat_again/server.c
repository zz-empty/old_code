#include "tcp.h"

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);
    printf("server pid = %d\n", getpid());

    int ret = 0;
    //create socket
    int sfd = tcpInit(argv[1], argv[2]);

    //create epoll
    int epfd = epoll_create(1);

    //add STDIN_FILENO to epoll
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;

    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    //add newFd to epoll
    event.data.fd = sfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);

    int newFd = 0;
    int readyNum = 0;
    char buf[64] = {0};
    struct epoll_event evs[2]; //epollwait的数量

    while (1) {
        //将需要监听的文件描述符加入到集合当中
        readyNum = epoll_wait(epfd, evs, 2, -1);
        ERROR_CHECK(readyNum, -1, "epoll_wait");
        printf("readyNum = %d\n", readyNum);

        for (int i = 0; i < readyNum; ++i) {
            if (evs[i].data.fd == STDIN_FILENO) {
                memset(buf, 0, sizeof(buf));
                read(STDIN_FILENO, buf, sizeof(buf));
                send(newFd, buf, strlen(buf)-1, 0);
            }

            if (evs[i].data.fd == sfd) {

                struct sockaddr_in cliAddr;
                memset(&cliAddr, 0, sizeof(cliAddr));
                socklen_t cliLen;
                newFd = accept(sfd, (struct sockaddr*)&cliAddr, &cliLen);
                ERROR_AND_CLOSE(newFd, -1, "accept", sfd);
                printf("%s %d success connect...\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

                /* newFd = tcpAccept(sfd); */
                /* newFd = accept(sfd, NULL, NULL); */
                event.data.fd = newFd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, newFd, &event);
                ERROR_CHECK(ret, -1, "EPOLL_CTL_ADD_newFd");
            }

            if (evs[i].data.fd == newFd) {
                memset(buf, 0, sizeof(buf));
                int ret = recv(newFd, buf, sizeof(buf), 0);
                if (0 == ret) {
                    printf("client exit\n");
                    close(newFd);
                    continue;
                }
                printf("buf = %s\n", buf);
            }
        }
    }
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
    memset(&cliAddr, 0, sizeof(cliAddr));
    socklen_t cliLen;
    int newFd = accept(sfd, (struct sockaddr*)&cliAddr, &cliLen);
    ERROR_AND_CLOSE(newFd, -1, "accept", sfd);
    printf("%s %d success connect...\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
    return newFd;
}
