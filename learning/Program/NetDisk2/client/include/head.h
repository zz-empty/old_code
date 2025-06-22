#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/sendfile.h>

//检查命令行参数个数
#define ARGS_CHECK(argc, num) {if (argc != num) {\
    fprintf(stderr, "Args error\n");\
    exit(-1);}}

//检查系统调用返回值
#define EXIT_CHECK(ret, num, msg) if (ret == num) {\
    do {\
        perror(msg);\
        exit(-1);\
    }while(0); }

#endif
