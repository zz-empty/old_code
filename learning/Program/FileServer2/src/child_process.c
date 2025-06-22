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
    int exit_flag;//子进程退出标志位

    while (1) {
        //阻塞，等待主进程发送客户端套接字
        recvFd(pipefd, &cli_fd, &exit_flag);
        if (1 == exit_flag) {
            printf("child_process exit!\n");
            exit(10);//退出码范围 0-255
        }

        //开始干活，4中干活方式，后三种是零拷贝发送文件
        char filename[] = "file";
        /* send_file_truck(cli_fd, filename); */
        /* send_file_mmap(cli_fd, filename); */
        /* send_file_sendfile(cli_fd, filename); */
        send_file_splice(cli_fd, filename);
        

        //干完通知主进程
        write(pipefd, "a", 1);
    }

    return 0;
}
