#include "../include/process_pool.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int child_process(int pipefd)
{
    printf("create child_process , child_pid = %d\n", getpid());
    int cli_fd;//客户端套接字

    while (1) {
        //阻塞，等待主进程发送客户端套接字
        recvFd(pipefd, &cli_fd);

        //开始干活
        char filename[] = "file";
        send_file(cli_fd, filename);

        //干完通知主进程
        write(pipefd, "a", 1);
    }

    return 0;
}
