#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/time.h>

//检查命令行参数个数
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Argc error!\n");\
    return -1;}}

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;}}

//从服务器下载文件，用while+recv+小货车的方式
int recv_file_truck(int sfd);

//从服务器下载文件，用mmap的方式
int recv_file_mmap(int sfd);

//从服务器下载文件，用splice的方式
int recv_file_splice(int sfd);


int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    //从配置文件中拿到服务器的ip和port
    FILE *fp = fopen(argv[1], "r");
    char ip[128] = {0};
    int port = 0;
    fscanf(fp, "%s%d", ip, &port);
    fclose(fp);

    //生成一个tcp类型的套接字，并连接上了服务器
    int sfd = 0;
    /* tcp_connect(ip, port, &sfd); */
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    //连接服务器
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(port);
    int ret = -1;

    ret = connect(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("connect server!\n");

    //计算下载时间，用gettimeofday接口
    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin, NULL);

    //下载文件
    recv_file_truck(sfd);
    /* recv_file_mmap(sfd); */
    /* recv_file_splice(sfd); */

    gettimeofday(&end, NULL);
    printf("cost time : %ld us\n", (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec);

    //关闭服务器套接字
    close(sfd);
    return 0;
}
