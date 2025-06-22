#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <sys/mman.h>

//检查系统调用返回值
#define EXIT_CHECK(ret, num, msg) if (ret == num) {\
    do {\
        perror(msg);\
        return -1;\
    }while(0); }

#endif
