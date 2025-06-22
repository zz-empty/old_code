#include "../include/head.h"
#include "../include/thread_pool.h"

int epoll_del(int epfd,int fd)
{
    struct epoll_event event;
    memset(&event,0,sizeof(event));

    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");

    return 0;
}

