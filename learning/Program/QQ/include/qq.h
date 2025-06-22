#ifndef __QQ_H__
#define __QQ_H__

//检查系统调用返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;} }

//用户信息
typedef struct {
    char _online;//是否在线
    int _usrfd;//用户套接字
    char _usrname[30];//用户名
}Usr_t, *pUsr_t;

//输入：服务器的ip地址，端口号
//输出：绑定了服务器ip和端口的，正在监听的套接字
int tcp_init(char *ip, int port);

//功能：服务器主进程处理来自用户的连接，发信息，退出
//参数：服务器套接字，用户数组，用户最大容量
int interact_usr(int sfd, pUsr_t pUsrArr, int max_capacity);

#endif
