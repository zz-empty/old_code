#include <stdio.h>
#include <string.h>
#include <unistd.h>

//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//send
#include <sys/socket.h>
//sendfile
#include <sys/sendfile.h>


#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg); return -1;} }


//传输文件协议：小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[1000];//火车车厢，表示数据
}Truck_t;

//使用sendfile传输数据，给另一个进程传输文件
int send_file_sendfile(int socket_fd, char *filename)
{
    int ret = -1;
    //定义一个小货车
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
    printf("filesize = %ld\n", file_info.st_size);


    //再发文件内容
    //用sendfile接口，整体传输
    sendfile(socket_fd, file_fd, 0, file_info.st_size);

    //关闭传输文件
    close(file_fd);
    return 0;
}

