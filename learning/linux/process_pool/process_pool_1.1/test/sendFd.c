#include <func.h>

int sendFd(int pipeFd, int fd) {
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));

    //init iovec
    char buf[6] = {0};
    strcpy(buf, "hi");
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);

    //set iovec
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    //init cmsghdr
    int len = CMSG_LEN(sizeof(len));//cmsg的长度,包含三个成员和可变数组
    struct cmsghdr *cmsg = (struct cmsghdr*)calloc(1, len);

    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg) = fd;

    //set cmsg
    msg.msg_control = cmsg;
    msg.msg_controllen = len;

    //send fd
    sendmsg(pipeFd, &msg, 0);
    return 0;
}

int recvFd(int pipeFd, int *fd) {
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));

    //init iovec
    char buf[6] = {0};
    strcpy(buf, "hi");
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);

    //set iovec
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    //init cmsg
    int len = CMSG_LEN(sizeof(len));//cmsg的长度,包含三个成员和可变数组
    struct cmsghdr *cmsg = (struct cmsghdr*)calloc(1, len);

    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;

    //set cmsg
    msg.msg_control = cmsg;
    msg.msg_controllen = len;

    //recv  fd
    recvmsg(pipeFd, &msg, 0);
    *fd = *(int*)CMSG_DATA(cmsg);
    return 0;
}

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 2);
    int sfd[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, sfd);

    if (fork()) {
        close(sfd[0]);

        int fd = open(argv[1], O_RDWR);
        printf("fd = %d\n", fd);
        /* write(fd, "what", 4); */
        sendFd(sfd[1], fd);

        wait(NULL);
    }
    else {
        close(sfd[1]);
        int nfd = 0;

        recvFd(sfd[0], &nfd);
        printf("nfd = %d\n", nfd);

        char buf[64] = {0};
        read(nfd, buf, sizeof(buf));
        printf("buf = %s\n", buf);

        exit(0);
    }
    return 0;
}

