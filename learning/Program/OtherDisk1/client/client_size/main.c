#include "func.h"

int main(int argc,char*argv[])
{
    ARGS_CHECK(argc,3);//开始要传两个参数，一个是IP地址，一个是端口号
    //初始化一个socket描述符，用于进行tcp通信
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in ser_addr;
    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
    ser_addr.sin_port = htons(atoi(argv[2]));

    int ret = 0;
    ret = connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));//为了实现向前兼容，这里要将ser_addr强转成struct sockaddr *的类型
    ERROR_CHECK(ret,-1,"connect");

    struct timeval begin,end;
    memset(&begin,0,sizeof(begin));
    memset(&end,0,sizeof(end));

    gettimeofday(&begin,NULL);

    int data_len = 0;
    char buf[1000] = {0};
    //先接文件名
    ret = recvCycle(sfd,&data_len,4);//接收火车头
    if(-1 == ret){
        printf("\n");
        return -1;
    }
    ret = recvCycle(sfd,buf,data_len);
    if(-1 == ret){
        return -1;
    }
    int fd = open(buf,O_RDWR|O_CREAT,0666);//创建一个新文件
    ERROR_CHECK(fd,-1,"open");
    //再接文件大小
    off_t filesize = 0;//文件的大小
    /* off_t last_filesize = 0;//文件的大小 */
    /* off_t download_now_size = 0;//当前下载的文件大小 */
    /* off_t slice_size = 0;//当前下载的文件大小 */
    ret = recvCycle(sfd,&data_len,4);
    if(-1 == ret){
        return -1;
    }
    ret = recvCycle(sfd,&filesize,data_len);
    if(-1 == ret){
        return -1;
    }
    printf("filesize = %ld\n",filesize);
    //时间设计
    //slice_size = filesize/10000;

    ftruncate(fd, filesize);
    char *pMap = (char *)mmap(NULL,filesize,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
    ERROR_CHECK(pMap,(char *)-1,"mmap");
    recv(sfd,pMap,filesize,MSG_WAITALL);
    munmap(pMap,filesize);

    /* while(1){ */
    /*     ret = recvCycle(sfd,&data_len,4); */
    /*     if(-1 == ret){ */
    /*         return -1; */
    /*     } */
    /*     if(data_len>0){ */
    /*         ret = recvCycle(sfd,buf,data_len); */
    /*         if(-1 == ret){ */
    /*             break; */
    /*         } */
    /*         write(fd,buf,data_len); */
    /*         download_now_size += data_len; */
    /*         if( download_now_size- last_filesize >= slice_size){ */
    /*             printf("%5.2f%%\r",(double)download_now_size/filesize*100); */
    /*             fflush(stdout); */
    /*             last_filesize = download_now_size; */
    /*         } */
    /*     } */
    /*     else{ */
    /*         printf("100.00%%\n"); */
    /*         break; */
    /*     } */
    /* } */
    gettimeofday(&end,NULL); 
    printf("cost time is %ldusec\n",1000000*(end.tv_sec - begin.tv_sec)+ end.tv_usec - begin.tv_usec  ); 
    close(fd);
    close(sfd);
}
