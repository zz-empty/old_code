#include <stdio.h>  
#include <time.h>  
  
int main() {  
    // 声明time_t和tm结构体变量  
    time_t rawtime;  
    struct tm * timeinfo;  
  
    // 获取当前时间  
    time(&rawtime);  
  
    // 将time_t转换为本地时间  
    timeinfo = localtime(&rawtime);  
  
    // 打印当前时间  
    printf("当前时间: %d-%02d-%02d %02d:%02d:%02d\n",  
           timeinfo->tm_year + 1900, // 年份是从1900年开始的  
           timeinfo->tm_mon + 1,     // 月份是从0开始的  
           timeinfo->tm_mday,        // 日  
           timeinfo->tm_hour,        // 小时  
           timeinfo->tm_min,         // 分钟  
           timeinfo->tm_sec);        // 秒  
  
    return 0;  
}
