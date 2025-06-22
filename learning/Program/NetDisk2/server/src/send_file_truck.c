#include "head.h"
#include "func.h"

//小于100M的发送方式
int send_file_truck(int fd_client, char *filename)
{
    //打开传输文件
    int fd_file = open(filename, O_RDONLY);
    EXIT_CHECK(fd_file, -1, "open");
    Truck_t truck;	 //定义一个小货车，用来传输文件
    int ret = -1;

    //断点续传
    //从客户端接收文件大小，如果大于0就偏移文件指针
    off_t offset = 0;
    recv(fd_client, &offset, sizeof(int), 0); 
    printf("offset:%ld\n", offset);
    if (offset) {
        lseek(fd_file, offset, SEEK_SET);
    } 

    //再发文件内容
    while (1) {
        memset(&truck, 0, sizeof(Truck_t));
        truck._data_len = read(fd_file, truck._data, sizeof(truck._data));
        if (0 == truck._data_len) {
            //传输完成，通知客户端，然后退出循环
            ret = send(fd_client, &truck._data_len, 4, 0);
            EXIT_CHECK(ret, -1, "send");
            //关闭传输文件
    		close(fd_file);
            return 0;
        }

        ret = send(fd_client, &truck, sizeof(int) + truck._data_len, 0);
        if (-1 == ret) {
            //客户端异常断开，退出循环
            printf("client erupt!\n");
            //关闭传输文件
    		close(fd_file);
            return -2;
        }
    }
}
