#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h> 
#include <syslog.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>

#include <pthread.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#include <sys/epoll.h>

#include <sys/uio.h>
#include <sys/sendfile.h>

#define ARGS_CHECK(argc,num) {if(argc != num)\
    {   fprintf(stderr, "args error!\n");\
        return -1;}     }
#define ERROR_CHECK(ret,num,msg) {if(ret == num)\
    {   perror(msg);\
        return -1;}     }
#define THREAD_ERROR_CHECK(ret, funcName)\
    do{\
        if(0 != ret){\
            printf("%s : %s\n", funcName, strerror(ret));\
        }\
    }while(0);

typedef struct {
    short flag;
    int pipeFd; //传输管道
    pid_t pid;
}process_data_t, *pProcess_data_t;

int makeChilds(int processNum, pProcess_data_t pData);
int childFunc(int pipeFd);
int tcpInit(char *ip, char *port, int *sockFd);
int epollAddFd(int fd, int epfd);
int sendFd(int pipeFd, int fd);
int recvFd(int pipeFd, int *fd);
int transFile(int pipeFd);

typedef struct {
    int data_len;
    char buf[1000];
}Train_t, *pTrain_t;
