#include <stdlib.h>

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
    int _flag;
    int _pipefd; //套接口
    pid_t _pid;
}ProcInfo_t, *pProcInfo_t;

int init_process_pool(pProcInfo_t pChilds, int childsNum);
int child_process(int pipeFd);
int tcp_init(char *ip, int port);
int epollAddFd(int fd, int epfd);
int sendFd(int pipeFd, int fd);
int recvFd(int pipeFd, int *fd);
int send_file(int pipeFd, char *filename);
int interact_cli(int sfd, pProcInfo_t pData, int processNum, int exitPipe);

