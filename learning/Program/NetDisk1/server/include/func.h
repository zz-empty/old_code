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

//传输文件协议：小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[BUF_SIZE];//火车车厢，表示数据
}Truck_t;

void conf_get(char *conf, char *ip, int *port, int *thread_num); //从配置文件中获取参数
socket_t tcp_init(char *ip, int port); //返回一个正在监听的tcp类型的服务器套接字
void *child_handle(void* p); //子线程的具体工作
int upload(int fd_socket, char *filename); //上传文件
int download(int fd_socket, char *filename); //下载文件
int epoll_add(int fd, int epfd);   //将fd加入epfd
int epoll_del(int fd, int epfd);   //将fd从epfd里删除
void print_cmd(pCmd_t pcmd); //打印命令
#endif
