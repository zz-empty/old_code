#include "../include/head.h"

int tcp_init(char * ip,char *port,int *psfd)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");

    struct sockaddr_in ser_addr;
    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(ip);
    ser_addr.sin_port = htons(atoi(port));

    int ret = 0;
    int reuse = 1;
    ret = setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    ERROR_CHECK(ret,-1,"setsockopt");
    //初始化socket描述符之后，开始将ip地址和端口号绑定到sfd上
    ret = bind(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));//为了实现向前兼容，这里要将ser_addr强转成struct sockaddr *的类型
    ERROR_CHECK(ret,-1,"bind");
    ret = listen(sfd,10);//端口激活，支持最大的并发量为10
    ERROR_CHECK(ret,-1,"listen");

    *psfd = sfd;
    return 0;
}

