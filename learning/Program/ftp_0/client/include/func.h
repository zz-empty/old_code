#ifndef __FUNC_H__
#define __FUNC_H__

//接收发送缓冲区大小
#define BUF_SIZE 1024

#define MAX_WORDNUM 8
#define MAX_WORDLEN 30

//套接字类型
typedef int socket_t;

//传输小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[BUF_SIZE];//货车车厢，表示数据
}Truck_t;

//通讯类型
typedef struct {
	int  _sess_fd ;             //对端套接字
	char _sess_buf[BUF_SIZE] ;  //发送接收缓冲区
}Session_t, *pSession_t;

//命令类型
typedef struct {
    int _argc;       //命令中有几个参数
    char _cmd[MAX_WORDNUM][MAX_WORDLEN];
}Cmd_t, *pCmd_t;

void conf_get(char *conf, char *ip, char *port);//从配置文件中获取参数
int tcp_connect(char *ip, int port);//连接服务器
int upload(int fd_socket, char *filename);//上传文件
int download(int fd_socket, char *filename);//下载文件
int sendn(int fd_send, char *buf_send, int len);//向fd，发送len长度的数据，从buf_send缓冲区
int recvn(int fd_recv, char *buf_recv, int len);//从fd中接收len长度的数据，放入buf_recv

void init_cmd(char *line, pCmd_t pcmd); //将line分割，存入cmd
void print_cmd(pCmd_t pcmd); //打印命令
int cmd_check(pCmd_t pcmd);//检查命令是否合法
#endif
