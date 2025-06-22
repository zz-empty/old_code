#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <pthread.h>

//检查命令行参数个数
#define ARGS_CHECK(argc, num) { if (argc != num) {\
    fprintf(stderr, "Args error!\n");\
    return -1;} }

//检查系统调用的返回值
#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg);\
    return -1;} }

int tcp_init(char *ip, int port);

#endif
