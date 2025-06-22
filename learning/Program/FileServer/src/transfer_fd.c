#include "../include/process_pool.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
/* #include <sys/uio.h>    //writev & readv */


//功能：将客户端套接字发送给子进程
//参数：子进程套接口，客户端套接字
int sendFd(int pipefd, int cli_fd)
{
    //使用sendmsg接口发送fd
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    
    //设置iovec结构体数组，不想传数据就随意写一个
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    char buf[6] = "hi"; //要传输的数据，不想传就随意写
    iov.iov_base = buf; 
    iov.iov_len = strlen(buf);

    msg.msg_iov = &iov;//iovec结构体数组指针
    msg.msg_iovlen = 1;//iovec结构体数组大小

    //设置cmsghdr结构体，最后一个成员就是要传输的fd
    struct cmsghdr *cmsg = (struct cmsghdr*)calloc(1, sizeof(struct cmsghdr));
    //计算cmsg结构体的长度, 使用CMSG_LEN()宏，其中已经有cmsg前三个成员的大小，只需传入最后一个成员大小即可（客户端套接字）
    int len = CMSG_LEN(sizeof(cli_fd));
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg) = cli_fd;

    msg.msg_control = cmsg;//cmsghdr结构体指针
    msg.msg_controllen = len;//cmsghdr结构体长度

    //将fd写入套接口
    int ret = sendmsg(pipefd, &msg, 0);
    ERROR_CHECK(ret, -1, "sendmsg");
    return 0;
}

//功能：从主进程接收客户端套接字
//参数：子进程套接口，客户端套接字地址
int recvFd(int pipefd, int *cli_fd)
{
    //使用recvmsg接口接收fd
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
        
    //设置iovec结构体数组，不想传数据就随意写一个
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    char buf[6] = "hi"; //要传输的数据，不想传就随意写
    iov.iov_base = buf; 
    iov.iov_len = strlen(buf);

    msg.msg_iov = &iov;//iovec结构体数组指针
    msg.msg_iovlen = 1;//iovec结构体数组大小

    //设置cmsghdr结构体，最后一个成员就是要接收的fd
    struct cmsghdr *cmsg = (struct cmsghdr*)calloc(1, sizeof(struct cmsghdr));
    //计算cmsg结构体的长度, 使用CMSG_LEN()宏，其中已经有cmsg前三个成员的大小，只需传入最后一个成员大小即可（客户端套接字）
    int len = CMSG_LEN(sizeof(cli_fd));
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;

    msg.msg_control = cmsg;//cmsghdr结构体指针
    msg.msg_controllen = len;//cmsghdr结构体长度

    //从套接口中接收fd
    recvmsg(pipefd, &msg, 0);
    *cli_fd = *(int*)CMSG_DATA(cmsg);
    return 0;
}
