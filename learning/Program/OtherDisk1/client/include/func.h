#ifndef __FUNC__
#define __FUNC__
#include "head.h"

#define FILENAME "file"
#define MAX_TOKEN 17
#define MSG_BUF 1000
#define TRAIN_BUF 1024
#define MAX_WORDNUM 5
#define MAX_WORDLEN 30
#define MAX_PATH 128
#define MAX_USER 1000

typedef struct{//定义文件发送协议，使用小火车
    int data_len;//“火车头”，存储车厢上到底有多少需要的数据
    char buf[TRAIN_BUF];//装数据的车厢
}train_t, *pTrain_t;

typedef  struct{
    char msg_type;//消息类型，l:长命令,s:短命令,m:通知信息,d:数据信息
    char msg_from;//c表示来自客户端,s表示来自服务器端
    char is_trust;//是否开启信任机制,1表示开启信任机制，0表示不开启信任机制
    int id;//当msg_from判断为c的时候，表明该消息来自于客户端，可以通过此处的id结合数据库或者结合token进行登录判断
    char token[MAX_TOKEN];
    char buf[MSG_BUF];
}msg_t, *pMsg_t;

typedef struct{
    int word_num;//存储命令里有几个参数
    char command_content[MAX_WORDNUM][MAX_WORDLEN];
}command_t, *pCommand_t;

typedef struct{
    int user_id;//用户的唯一标识符
    int connect_fd;//本次链接的唯一标识符，对应标识其在active_user_table中的位置
    int cur_path_id;//用户当前所在的路径id
    char cur_path[MAX_PATH];
}active_user_node_t, *pActive_user_node_t;

typedef struct{
    int tcp_sfd;//监听tcp链接的fd
    int tcp_epfd;//记录监听的epoll的fd
    int connect_num;//记录此时链接的客户端数量
    active_user_node_t active_user_table[MAX_USER];//维护一个由活跃用户结点组成的活跃用户表
    int is_active[MAX_USER];//标记一下具体哪些fd的用户处于活跃状态，方便进行集体操作
}server_sys, *pServer_sys;

typedef struct{
    char is_login;//记录是否已经登录
    int user_id;//唯一用户对应的id
    int epfd;//记录epoll监听的fd
    char cur_path[MAX_PATH];//记录当前路径
}client_sys, *pClient_sys;

typedef struct{
    int user_id;
    char salt[16];
    char username[20];
    char cryptpasswd[128];
}userinfo_t, *pUserinfo_t;

typedef struct{
    char type[1];
    int file_id;
    int parent_id;
    int owner_id;
    int filesize;
    char filename[20];
    char username[20];
    char md5[20];
}fileinfo_t, *pfileinfo_t;

typedef struct{
    int parent_id;
    int owner_id;
    char username[20];
    char cur_path[128];
    char last_path[128];
}path_t,*pPath_t;

int epoll_add(int epfd,int fd);
int user_registration(int fd);
int user_login(int fd);
int command(char choice, pTrain_t p, int sfd);

#endif

