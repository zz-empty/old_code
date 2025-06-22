#ifndef __HEAD__
#define __HEAD__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<signal.h>
#include<strings.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/epoll.h>
#include<sys/sendfile.h>
#include <mysql/mysql.h>
#include <shadow.h>
#include <crypt.h>

#define ARGS_CHECK(argc,val) {if(argc!=val) {printf("error args\n"); return -1;}}
#define ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName) {if(ret!=0){printf("%s failed %s\n",funcName,strerror(ret));return -1;}}
#define ERROR_EXIT(msg) do{perror(msg);exit(1);}while(0)

#endif
