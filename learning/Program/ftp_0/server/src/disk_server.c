#include "head.h"
#include "func.h"

void sig_handle(int signum)
{
    //回收子进程资源
    wait(NULL);
    /* printf("client exit!\n"); */
    signum = 0;
}

int main(int argc, char *argv[]) 
{
    //参数：配置文件路径
    if (2 != argc) {
        fprintf(stderr, "Args error!\n");
        return -1;
    }

    //注册子进程退出信号，用于异步回收子进程资源
    signal(SIGCHLD, sig_handle);

    //从配置文件中拿到 服务器ip和port
    char ip[16] = "";
    char port[10] = "";
    conf_get(argv[1], ip, port);

    //建立tcp监听
    socket_t fd_server = tcp_init(ip, atoi(port));
    EXIT_CHECK(fd_server, -1, "socket_init");
    socket_t fd_client;
    pSession_t ps;//通信类型
    printf("DiskServer[ip:%s, port:%s] boot...\n", ip, port);

    //等待客户端连接
    int client_num = -1;//客户端的fd序号
    char buf[128] = "";//读写缓冲区
    int pid;  //子进程id
    while (1) {
        fd_client = accept(fd_server, NULL, NULL);
        EXIT_CHECK(fd_client, -1, "accept");

        //显示客户端连接
        bzero(buf, sizeof(buf));
        sprintf(buf, "%d connect...\n", ++client_num);
        write(1, buf, sizeof(buf)); 

        //交给子进程处理
        ps = (pSession_t)calloc(1, sizeof(Session_t));
        ps->_sess_fd = fd_client;
        pid = fork();
        if (0 == pid) {
            child_handle(ps);
            exit(-1);
        }
    }

    return 0;
}
