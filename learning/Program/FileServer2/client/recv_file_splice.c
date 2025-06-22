#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;}}

//从服务器下载文件，用splice的方式
int recv_file_splice(int sfd)
{
    int ret = -1;
    //先接收文件名字
    int data_len = 0;
    char filename[1000] = {0};
    recv(sfd, &data_len, sizeof(int), 0);
    recv(sfd, filename, data_len, 0);

    //创建一个新文件
    int file_fd = open(filename, O_RDWR | O_CREAT, 0600);
    ERROR_CHECK(file_fd, -1, "open");


    //再接收文件大小
    off_t filesize = 0;//此处类型必须为off_t，否则ftrucate会失败
    recv(sfd, &data_len, sizeof(int), 0);
    recv(sfd, &filesize, data_len, 0);
    printf("filesize: %ld\n", filesize);

    //用splice接收文件
    int fds[2];
    pipe(fds);
    int cur_len = 0; //当前接收长度
    int maxsize = 4096;//每次传输的最大字节数
    
    printf("recv start...\n");
    while (cur_len < filesize) {
        ret = splice(sfd, 0, fds[1], 0, maxsize, 0);
        ret = splice(fds[0], 0, file_fd, 0, ret, 0);
        cur_len += ret;
    }
    printf("recv finish!\n");

    //关闭文件
    close(file_fd);
    return 0;
}
