#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;}}

//从服务器下载文件，用mmap的方式
int recv_file_mmap(int sfd)
{
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

    //用mmap接收文件
    int ret = ftruncate(file_fd, filesize);
    ERROR_CHECK(ret, -1, "ftruncate");
    
    printf("recv start...\n");
    char *pMap = (char*)mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, file_fd, 0);
    ERROR_CHECK(pMap, (char*)-1, "mmap");

    recv(sfd, pMap, filesize, MSG_WAITALL);

    munmap(pMap, filesize);
    printf("recv finish!\n");

    //关闭文件
    close(file_fd);
    return 0;
}
