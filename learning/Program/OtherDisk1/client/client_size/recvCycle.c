#include <func.h>

int recvCycle(int sfd,void *pstart,int len)//定义循环接收函数，封装recv函数
{
    char *p = (char *)pstart;
    int total = 0;
    int ret = 0;
    while(total < len){
        ret = recv(sfd,p+total,len-total,0);
        if( 0 == ret){
            printf("\n");
            return -1;
        }
        total += ret;//每次接收到的字节加到total上
    }

    return 0;
}

