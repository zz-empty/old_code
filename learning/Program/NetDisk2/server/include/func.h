#ifndef __FUNC_H__
#define __FUNC_H__
#include "head.h"

//缓冲区大小
#define BUF_SIZE 1024
//命令最多有几个参数
#define MAX_WORDNUM 8
//命令参数的最大长度
#define MAX_WORDLEN 30
//100 MB
#define HUNDRED_MEGABYTE 104857600

//套接字类型
typedef int socket_t;

//命令类型
typedef struct {
    int _argc;       //命令中有几个参数
    char _cmd[MAX_WORDNUM][MAX_WORDLEN];
}Cmd_t, *pCmd_t;

//传输文件协议：小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[BUF_SIZE];//火车车厢，表示数据
}Truck_t, *pTruck_t;

void conf_get(char *conf, char *ip, int *port, int *thread_num); //从配置文件中获取参数
socket_t tcp_init(char *ip, int port); //返回一个正在监听的tcp类型的服务器套接字
void *child_handle(void* p); //子线程的具体工作
int epoll_add(int fd, int epfd);   //将fd加入epfd
int epoll_del(int fd, int epfd);   //将fd从epfd里删除
void print_cmd(pCmd_t pcmd); //打印命令
int login_varify(socket_t fd, pTruck_t pT); //验证客户端的用户名和密码

//执行命令，并向客户端发送命令结果
int do_ls(socket_t fd_client, pTruck_t pT);
int do_pwd(socket_t fd_client, pTruck_t pT);
int do_cd(socket_t fd_client, pTruck_t pT, pCmd_t pcmd);
int do_rm(socket_t fd_client, pTruck_t pT, pCmd_t pcmd);
int do_mkdir(socket_t fd_client, pTruck_t pT, pCmd_t pcmd);
int do_puts(socket_t fd_client, pTruck_t pT, pCmd_t pcmd);
int do_gets(socket_t fd_client, pTruck_t pT, pCmd_t pcmd);

void record_client_msg(int fd_log, socket_t fd_client, const char *rank, const char *msg);  //记录普通日志
void record_client_cmd(int fd_log, socket_t fd_client, const char *rank, pCmd_t pcmd);  //记录命令日志

int get_filesize(char *filename); //获取文件大小
int send_file_truck(int fd_client, char *filename); //小于100M的发送方式
int send_file_sendfile(int fd_client, char *filename, off_t filesize); //文件大于100M, 用sendfile发送文件
int recv_file_truck(int fd_socket, char *filename); //小于100M的接收方式
int recv_file_mmap(int fd_socket, char *filename, off_t filesize); //大于100M，用mmap接收
#endif
