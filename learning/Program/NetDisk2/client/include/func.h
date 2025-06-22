#ifndef __FUNC_H__
#define __FUNC_H__

#include "head.h"

//接收发送缓冲区大小
#define BUF_SIZE 1024
//命令中最多有几个参数
#define MAX_WORDNUM 8
//命令一个参数的最大长度
#define MAX_WORDLEN 30
//100 M
#define HUNDRED_MEGABYTE 104857600


//套接字类型
typedef int socket_t;

//传输小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[BUF_SIZE];//货车车厢，表示数据
}Truck_t, *pTruck_t;

//命令类型
typedef struct {
    int _argc;       //命令中有几个参数
    char _cmd[MAX_WORDNUM][MAX_WORDLEN];
}Cmd_t, *pCmd_t;

void conf_get(char *conf, char *ip, char *port);//从配置文件中获取参数
int tcp_connect(char *ip, int port);//连接服务器
int user_login(socket_t fd_server, pTruck_t pT); //如果登录成功返回1，失败返回0

void init_cmd(char *line, pCmd_t pcmd); //将line分割，存入cmd
void print_cmd(pCmd_t pcmd); //打印命令

int get_filesize(char *filename); //获取文件大小
int recv_file_truck(int fd_socket, char *filename); //小于100M的接收方式
int recv_file_mmap(int fd_socket, char *filename, off_t filesize); //大于100M，用mmap接收
int send_file_sendfile(int fd_socket, char *filename, int filesize); //文件大于100M, 用sendfile发送文件
int send_file_truck(int fd_socket, char *filename);//小于100M的发送方式
#endif
