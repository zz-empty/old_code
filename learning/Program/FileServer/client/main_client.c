#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>


//检查命令行参数个数
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Argc error!\n");\
    return -1;}}

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;}}

//接收协议
typedef struct {
    int _data_len;//先接数据长度
    char _data[1000];//再接数据内容
}Truck_t;

int main(int argc, char *argv[])
{
    //从配置文件中拿到服务器的ip和port
    ARGS_CHECK(argc, 2);
    FILE *fp = fopen(argv[1], "r");
    char ip[128] = {0};
    int port = 0;
    fscanf(fp, "%s%d", ip, &port);
    fclose(fp);

    //生成一个tcp类型的套接字，用于连接服务器
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    //连接服务器
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(port);
    int ret = -1;
    ret = connect(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "connect");

    //接收文件
    Truck_t truck;
    memset(&truck, 0, sizeof(truck));
    //先接收文件名，打开一个新文件
    recv(sfd, &truck._data_len, sizeof(int), 0);
    recv(sfd, truck._data, truck._data_len, 0);
    int file_fd = open(truck._data, O_RDWR|O_CREAT, 0666);
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
    while (1) {
        //重置小货车
        memset(&truck, 0, sizeof(truck));
        //先接数据长度
        recv(sfd, &truck._data_len, sizeof(int), 0);
        if (0 == truck._data_len) {
            //传输完毕
            printf("Transfer Finish!\n");
            break;
        }
        //根据长度，接收数据内容
        //防止发送方发的慢，导致接收缓冲区将车厢当成车头，设置recv参数为MSG_WAITALL
        ret = recv(sfd, truck._data, truck._data_len, MSG_WAITALL);

        //打印进度条
        cur_size += ret;
        rate = (float)cur_size / total_size;
        printf("--------------------------%5.2f%%\r", rate * 100);
        fflush(stdout);//防止光标抖动

        //将接收数据写入文件
        write(file_fd, truck._data, truck._data_len);
    }

    //关闭文件
    close(file_fd);

    //关闭服务器套接字
    close(sfd);
    return 0;
}
