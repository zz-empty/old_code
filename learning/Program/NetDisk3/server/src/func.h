#ifndef __FUNC_H__
#define __FUNC_H__
#include "head.h"

#define BUF_SIZE 1024   //缓冲区大小
#define MSG_SIZE 256    //消息大小
#define MAX_WORDNUM 8   //命令最多有几个参数
#define MAX_WORDLEN 30  //命令参数的最大长度
#define HUNDRED_MEGABYTE 104857600  //100 MB
#define USERNAME_SIZE 50 //用户名大小
#define PASSWD_SIZE 100 //密码大小
#define SALT_SIZE 30    //盐值大小
#define MAX_PATH 128    //路径长度

//套接字类型
typedef int socket_t;

//数据传输协议：小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[BUF_SIZE];//火车车厢，表示数据
}Truck_t, *pTruck_t;

//命令类型
typedef struct {
    int _argc;       //命令中有几个参数
    char _cmd[MAX_WORDNUM][MAX_WORDLEN];
}Cmd_t, *pCmd_t;

//传输的消息
typedef struct {
    char _type; //消息类型（d-登录，r-注册）
    char _buf[MSG_SIZE];//具体消息
}Msg_t, *pMsg_t;

//用户类型
typedef struct {
    int _user_id;
    char _username[USERNAME_SIZE];
    char _passwd[PASSWD_SIZE];
    char _salt[SALT_SIZE];
}User_t, *pUser_t;

//活跃用户节点
typedef struct{
    int _user_id;       //用户的唯一标识符
    int _connect_fd;    //本次链接的唯一标识符，对应标识其在active_user_table中的位置
    int _cur_path_id;   //用户当前所在的路径id
    char _cur_path[MAX_PATH]; //当前工作路径
}Active_user_node_t, *pActive_user_node_t;

int mysql_query1(char *query,char **result);
int mysql_insert(char *query);

void conf_get(char *conf, char *ip, int *port, int *thread_num); //从配置文件中获取参数
socket_t tcp_init(char *ip, int port); //返回一个正在监听的tcp类型的服务器套接字
int epoll_add(int fd, int epfd);   //将fd加入epfd
void *child_handle(void* p); //子线程的具体工作

void record_client_msg(int fd_log, socket_t fd_client, const char *rank, const char *msg);  //记录普通日志
void record_client_cmd(int fd_log, socket_t fd_client, const char *rank, pCmd_t pcmd);  //记录命令日志

int user_login(socket_t fd_client, pTruck_t pT, pActive_user_node_t pNode);
int user_register(socket_t fd_client, pTruck_t pT);

//执行命令，并向客户端发送命令结果
int do_ls(socket_t fd_client, pTruck_t pT);
int do_pwd(socket_t fd_client, pTruck_t pT);
int do_cd(socket_t fd_client, pTruck_t pT);
int do_rm(socket_t fd_client, pTruck_t pT);
int do_mkdir(socket_t fd_client, pTruck_t pT);
int do_puts(socket_t fd_client, pTruck_t pT);
int do_gets(socket_t fd_client, pTruck_t pT);

void print_cmd(pCmd_t pcmd); //打印命令

#endif
