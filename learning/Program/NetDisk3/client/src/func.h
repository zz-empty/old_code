#ifndef __FUNC_H__
#define __FUNC_H__

#include "head.h"

//接收发送缓冲区大小
#define BUF_SIZE 1024
//消息大小
#define MSG_SIZE 256
//命令中最多有几个参数
#define MAX_WORDNUM 8
//命令一个参数的最大长度
#define MAX_WORDLEN 30
//100 M
#define HUNDRED_MEGABYTE 104857600
//用户名大小
#define USRNAME_SIZE 50
//密码大小
#define PASSWD_SIZE 100
//salt值大小
#define SALT_SIZE 30


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

//传输的消息
typedef struct {
    char _type; //消息类型
    char _buf[MSG_SIZE];//消息大小
}Msg_t, *pMsg_t;

//用户类型
typedef struct {
    int _id;
    char _salt[SALT_SIZE];
    char _username[USRNAME_SIZE];
    char _passwd[PASSWD_SIZE];
}Usr_t, *pUsr_t;


void conf_get(char *conf, char *ip, char *port);//从配置文件中获取参数
int tcp_connect(char *ip, int port);//连接服务器

int login_client(socket_t fd_server, pTruck_t pT); //返回0登录成功，返回-1退出程序
int user_login(socket_t fd_server);
int user_register(socket_t fd_server);

int command_client(socket_t fd_server, pTruck_t pT); //发送命令，接收命令结果

#endif
