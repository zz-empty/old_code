#ifndef __PROCESSPOOL_H__
#define __PROCESSPOOL_H__

#include <stdlib.h>

//检查命令行参数个数
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Args error!\n"); return -1; }}

//检查系统调用返回值是否合法，非法报错退出
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror("msg");  return -1;  } }

//输入：服务器的ip地址，端口号
//输出：绑定了服务器ip和端口的，正在监听的套接字
int tcp_init(char *ip, int port);


//记录进程信息的结构体
typedef struct 
{
    short _flag;//进程是否空闲 0-是  1-不是
    int _pipefd;//父子进程通信的管道
    pid_t _pid;//进程id
}ProcInfo_t, *pProcInfo_t;

//功能：创建进程池
//参数：子进程数组，子进程数量
int init_process_pool(pProcInfo_t, int);

//功能：服务器主进程处理来自客户端的请求
//参数：服务器套接字，子进程数组，子进程数量，退出管道读端
int interact_cli(int sfd, pProcInfo_t pChilds, int childsNum, int exitpipe);

//功能：将客户端套接字发送给子进程
//参数：子进程套接口，客户端套接字
int sendFd(int pipefd, int cli_fd);

//功能：从主进程接收客户端套接字
//参数：子进程套接口，客户端套接字地址
int recvFd(int pipefd, int *cli_fd);

//功能：资源进程的配置
//参数：与主进程通信的套接字
int child_process(int pipefd);

//功能：给客户端套接字发送文件
//参数：客户端套接字，文件名
int send_file(int socket_fd, char *filename);

#endif
