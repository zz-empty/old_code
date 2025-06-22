#include "head.h"
#include "func.h"


//大于100M，用mmap接收
int recv_file_mmap(int fd_socket, char *filename, off_t filesize)
{
    int ret = -1;

    //打开或创建文件, 根据offset偏移文件指针
    int fd_file = open(filename, O_RDWR | O_CREAT, 0600);
    EXIT_CHECK(fd_file, -1, "open");

    //用mmap接收文件
    ret = ftruncate(fd_file, filesize);
    EXIT_CHECK(ret, -1, "ftruncate");
    
    printf("recv start...\n");
    char *pMap = (char*)mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, fd_file, 0);
    EXIT_CHECK(pMap, (char*)-1, "mmap");

    ret = recv(fd_socket, pMap, filesize, MSG_WAITALL);
    if (0 == ret) {
        //对端异常断开
        munmap(pMap, filesize);
        close(fd_file);
        return -2;
    }

    munmap(pMap, filesize);
    printf("recv finish!\n");

    //关闭文件
    close(fd_file);
    return 0;
}
