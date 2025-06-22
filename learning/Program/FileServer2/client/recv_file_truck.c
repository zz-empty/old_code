#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;}}

//接收协议:小货车
typedef struct {
    int _data_len;//车头，先接数据长度
    char _data[1000];//车厢，再接数据内容
}Truck_t;

//先接数据长度，再根据数据长度接收数据内容
int recv_file_truck(int sfd)
{
    int ret = -1;

    //接收文件
    Truck_t truck;
    memset(&truck, 0, sizeof(truck));
    //先接收文件名，打开一个新文件
    recv(sfd, &truck._data_len, sizeof(int), 0);
    recv(sfd, truck._data, truck._data_len, 0);

    int file_fd = open(truck._data, O_WRONLY|O_CREAT, 0666);
    ERROR_CHECK(file_fd, -1, "open");
    printf("filename: %s\n", truck._data);

    //再接收文件大小，用来打印进度条
    int total_size = 0;//文件总大小
    recv(sfd, &truck._data_len, sizeof(int), 0);
    recv(sfd, &total_size, truck._data_len, 0);
    printf("filesize: %d\n", total_size);

    float rate = 0;//当前接收百分比
    int cur_size = 0;//文件已接收大小

    //循环接收文件内容
    while (cur_size < total_size) {
        //重置小货车
        memset(&truck, 0, sizeof(truck));
        //先接数据长度
        recv(sfd, &truck._data_len, sizeof(int), 0);
        if (0 == truck._data_len) {
            //传输完毕
            printf("Transfer Finish!\n");
            break;
        }

        //根据数据长度接收数据内容
        //防止发送方发的慢，导致接收缓冲区将车厢当成车头，设置recv参数为MSG_WAITALL
        ret = recv(sfd, truck._data, truck._data_len, MSG_WAITALL);
        if (0 == ret) {
            printf("Download finish!\n");
            break;
        }

        //将接收数据写入文件
        write(file_fd, truck._data, ret);
        cur_size += ret;

        //打印进度条
        rate = (float)cur_size / total_size;
        printf("--------------------------%5.2f%%\r", rate * 100);
        fflush(stdout);//防止光标抖动
    }

    //关闭文件
    close(file_fd);

    return 0;
}
