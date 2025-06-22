#ifndef __FUNC_H__
#define __FUNC_H__

//接收发送缓冲区大小
#define BUF_SIZE 1024
//命令中最多有几个参数
#define MAX_WORDNUM 8
//命令一个参数的最大长度
#define MAX_WORDLEN 30

//套接字类型
typedef int socket_t;

//通讯类型
typedef struct {
	socket_t  _sess_fd ;             //对端套接字
	char _sess_buf[BUF_SIZE] ;  //缓冲区
}Session_t, *pSession_t ;

//命令类型
typedef struct {
    int _argc;       //命令中有几个参数
    char _cmd[MAX_WORDNUM][MAX_WORDLEN];
}Cmd_t, *pCmd_t;


void conf_get(char *conf, char *ip, char *port); //从配置文件中获取参数
int tcp_init(char *ip, int port); //返回一个正在监听的tcp类型的服务器套接字
int child_handle(pSession_t ps); //子进程的具体工作，与客户端交互
int upload(int fd_socket, char *filename); //上传文件
int download(int fd_socket, char *filename); //下载文件
#endif
