#include <stdio.h>
#include <string.h>
#include <unistd.h>

//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//send
#include <sys/socket.h>


#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg); return -1;} }

//传输文件协议：小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[1000];//火车车厢，表示数据
}Truck_t;

//使用私有协议传输数据，给另一个进程传输文件
int send_file(int socket_fd, char *filename)
{
    int ret = -1;
    //定义一个小货车，用来传输文件
    Truck_t truck;
    memset(&truck, 0, sizeof(Truck_t));

    //将文件名扩展为文件路径
    char filepath[128] = {0};
    sprintf(filepath, "../resource/%s", filename);

    //根据文件路径打开传输文件
    int file_fd = open(filepath, O_RDONLY);
    ERROR_CHECK(file_fd, -1, "open");

    //先发文件名
    truck._data_len = strlen(filename);
    strcpy(truck._data, filename);
    ret = send(socket_fd, &truck, sizeof(int) + truck._data_len, 0);
    ERROR_CHECK(ret, -1, "send_title");

    //再发文件大小
    struct stat file_info;
    memset(&file_info, 0, sizeof(file_info));
    fstat(file_fd, &file_info);

    truck._data_len = sizeof(file_info.st_size);
    memcpy(truck._data, &file_info.st_size, truck._data_len);
    ret = send(socket_fd, &truck, sizeof(int) + truck._data_len, 0);
    ERROR_CHECK(ret, -1, "send_filesize");


    //再发文件内容
    while (1) {
        memset(truck._data, 0, sizeof(truck._data));
        truck._data_len = read(file_fd, truck._data, sizeof(truck._data));
        ERROR_CHECK(truck._data_len, -1, "read");
        if (0 == truck._data_len) {
            //传输完成，通知客户端，然后退出循环
            ret = send(socket_fd, &truck._data_len, 4, 0);
            ERROR_CHECK(ret, -1, "send");
            break;
        }

        ret = send(socket_fd, &truck, sizeof(int) + truck._data_len, 0);
        if (-1 == ret) {
            //客户端异常断开，退出循环
            printf("client already break!\n");
            break;
        }
    }
    

    //关闭传输文件
    close(file_fd);
    return 0;
}
