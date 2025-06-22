#include "head.h"
#include "func.h"

//文件大于100M, 用sendfile发送文件
int send_file_sendfile(int fd_socket, char *filename, int filesize)
{
    //打开传输文件
    int fd_file = open(filename, O_RDONLY);
    EXIT_CHECK(fd_file, -1, "open");

    //发文件内容
    sendfile(fd_socket, fd_file, 0, filesize);

    //关闭传输文件
    close(fd_file);
    return 0;
}
