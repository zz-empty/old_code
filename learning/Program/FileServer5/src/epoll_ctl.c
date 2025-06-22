#include "../include/head.h"

//将fd加入epfd
int epoll_add(int fd, int epfd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    ERROR_CHECK(ret, -1, "EPOLL_CTL_ADD");
    return 0;
}

//将fd从epfd中移除
int epoll_del(int fd, int epfd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &event);
    ERROR_CHECK(ret, -1, "EPOLL_CTL_DEL");
    return 0;
}
