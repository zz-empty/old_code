#include "head.h"

//传输文件协议：小货车
#define BUF_SIZE 1024
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[BUF_SIZE];//火车车厢，表示数据
}Truck_t;

//上传文件
int upload(int fd_socket, char *filename)
{
    int ret = -1;
    //定义一个小货车，用来传输文件
    Truck_t truck;
    memset(&truck, 0, sizeof(Truck_t));

    //根据文件名打开传输文件
    int fd_file = open(filename, O_RDONLY);
    EXIT_CHECK(fd_file, -1, "open");

#if 0
    //发文件大小
    struct stat file_info;
    memset(&file_info, 0, sizeof(file_info));
    fstat(fd_file, &file_info);

    truck._data_len = sizeof(file_info.st_size);
    memcpy(truck._data, &file_info.st_size, truck._data_len);
    ret = send(fd_socket, &truck, sizeof(int) + truck._data_len, 0);
    EXIT_CHECK(ret, -1, "send_filesize");
#endif

    //发文件内容
    while (1) {
        memset(truck._data, 0, sizeof(truck._data));

        //读取文件
        truck._data_len = read(fd_file, truck._data, BUF_SIZE);
        if (0 == truck._data_len) {
            //传输完成，退出循环
            break;
        }

        //发送
        ret = send(fd_socket, &truck, sizeof(int) + truck._data_len, 0);
        if (-1 == ret) {
            //客户端异常断开，退出循环
            printf("client already break!\n");
            return -1;
        }
    }

    //传输完成，通知fd
    truck._data_len = 0;
    send(fd_socket, &truck._data_len, sizeof(int), 0);

    //关闭传输文件
    close(fd_file);
    return 0;
}

//下载文件
int download(int fd_socket, char *filename)
{
    //打开或创建一个文件
    int fd_file = open(filename, O_WRONLY | O_CREAT, 0600);
    EXIT_CHECK(fd_file, -1, "open");

#if 0
    //接收文件大小
    int filesize = 0;
    recv(fd_socket, &filesize, sizeof(int), 0);
    printf("filesize: %d", filesize);
#endif

    //接收文件内容
    Truck_t truck;
    while (1) {
        memset(&truck, 0, sizeof(truck));
        //接收数据长度
        recv(fd_socket, &truck._data_len, sizeof(truck._data_len), 0);
        if (0 == truck._data_len) {
            //文件传输完毕
            break;
        }
        //接收数据内容
        recv(fd_socket, truck._data, truck._data_len, MSG_WAITALL);
        write(fd_file, truck._data, truck._data_len);
    }

    close(fd_file);
    return 0;
}
