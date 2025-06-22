#ifndef __TCP_H__
#define __TCP_H__

//检查命令行参数个数
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Args error!\n"); return -1; }}

//检查系统调用返回值是否合法，非法报错退出
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror("msg");  return -1;  } }

//输入：配置文件（服务器的ip地址，端口号）
//输出：绑定了服务器ip和端口的，正在监听的套接字
int tcp_init(char *conf);

//服务端与客户端的交互
int interact_cli(int sfd);


#endif
