#include "head.h"
#include "func.h"

//记录普通日志
void record_client_msg(int fd_log, socket_t fd_client, const char *rank, const char *msg)
{
    //声明time_t和tm结构体变量  
    time_t rawtime;  
    struct tm * timeinfo;  

    //获取当前时间                                                                                                                                        
    time(&rawtime);  

    //将time_t转换为本地时间  
    timeinfo = localtime(&rawtime);  

    //拼接信息
    char buf[128] = "";
    sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d [fd:%d] [%s]\t%s\n",  
           timeinfo->tm_year + 1900, // 年份是从1900年开始的  
           timeinfo->tm_mon + 1,     // 月份是从0开始的  
           timeinfo->tm_mday,        // 日  
           timeinfo->tm_hour,        // 小时  
           timeinfo->tm_min,         // 分钟  
           timeinfo->tm_sec,        // 秒
           fd_client,
           rank,
           msg);

    //将信息写入日志文件
    write(fd_log, buf, strlen(buf));
}

//记录命令日志
void record_client_cmd(int fd_log, socket_t fd_client, const char *rank, pCmd_t pcmd)
{
    //声明time_t和tm结构体变量  
    time_t rawtime;  
    struct tm * timeinfo;  

    //获取当前时间                                                                                                                                        
    time(&rawtime);  

    //将time_t转换为本地时间  
    timeinfo = localtime(&rawtime);  

    //拼接信息
    char buf[128] = "";
    sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d [fd:%d] [%s]\t",  
           timeinfo->tm_year + 1900, // 年份是从1900年开始的  
           timeinfo->tm_mon + 1,     // 月份是从0开始的  
           timeinfo->tm_mday,        // 日  
           timeinfo->tm_hour,        // 小时  
           timeinfo->tm_min,         // 分钟  
           timeinfo->tm_sec,        // 秒
           fd_client,
           rank);

    //向信息内加入命令
    for (int i = 0; i < pcmd->_argc; ++i) {
        strcat(buf, pcmd->_cmd[i]);
        strcat(buf, " ");
    }
    strcat(buf, "\n");

    //将信息写入日志文件
    write(fd_log, buf, strlen(buf));
}
