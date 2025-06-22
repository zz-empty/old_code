#include "../include/head.h"
#include "../include/func.h"

int downloadfile(int sfd, train_t train_to_server, train_t train_to_client);
int uploadfile(int sfd, train_t train_to_server);

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
    //连接服务器端
    ret = connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));//为了实现向前兼容，这里要将ser_addr强转成struct sockaddr *的类型
    ERROR_CHECK(ret,-1,"connect");

    int handle = 0;
    while(1){
        printf("请选择你的操作:(输入序号)\n");
        printf("1、用户登录 2、用户注册 3、退出\n");
        scanf("%d",&handle);
        if(1 == handle){
            user_login(sfd);
            break;
        }
        else if(2 == handle){
            user_registration(sfd);
            continue;
        }
        else if(3 == handle){
            close(sfd);
            exit(0);
        }
        else{
            printf("输入不合法，请重新输入\n");
            continue;
        }

    }

    printf("登陆成功，欢迎使用网盘\n");
    //创建epoll                                                             
    int epfd = epoll_create(1);                                                 
    ERROR_CHECK(epfd, -1, "create");                                            

    struct epoll_event event, evs[2];                                           
    memset(&event, 0, sizeof(event));                                       

    event.events = EPOLLIN;                                                     
    /* event.data.fd = STDIN_FILENO; */                                     

    /* //将要监听的描述符加入红黑树 */                                          
    /* ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event); */           
    /* ERROR_CHECK(ret, -1, "epoll_ctl"); */                                    

    event.data.fd = sfd;                                                        

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);                          
    ERROR_CHECK(ret, -1, "ctl");                                                

    //小火车，用来数据通信                                                      
    msg_t msg;                                                                  
    train_t train_to_server;                                                    
    train_t train_to_client;                                                

    int readyNum = 0;                                                      



    /* user_registration(sfd); */                                           


    while(1){                                                               
        printf("what do you wanna do?\n");                                  
        printf("1:cd\n");                                                   
        printf("2:ls\n");                                                   
        printf("3:pwd\n");                                                  
        printf("4:rm\n");                                                   
        printf("5:mkdir\n");                                                
        printf("8:download\n");                                             
        printf("9:upload\n");                                               


        int choice = 0;                                                    
        /* char blank; */                                                         
        scanf("%d", &choice);                                               
        //scanf("%c",&blank);                                                 
printf("choice = %d\n", choice);
        command(choice, &train_to_server, sfd);                             


        /* while(1){ */                                                     
        //等待事件的发生                                                    
        printf("before wait\n");                                            
        readyNum = epoll_wait(epfd, evs, 2, -1);                            
        for(int i = 0; i < readyNum; ++i){                                  
            /* if(evs[i].data.fd == STDIN_FILENO){ */                       
            /*     char choice; */                                          
            /*     memset(&train, 0, sizeof(train)); */                     
            /*     read(STDIN_FILENO, &choice, sizeof(char)); */            
            /*     fflush(STDIN_FILENO);//清空标准输入 */                   
            /*     command(choice, &train, sfd); */                         
            /*     send(sfd, &train, train.data_len, 0); */                 
            /* } */                                                         
            if(evs[i].data.fd == sfd){                                      
                //1.0 与服务器通信                                          
                //2.0 下载文件                                              
                memset(&train_to_client, 0, sizeof(train_t));               
                memset(&msg, 0, sizeof(msg));                               
                int ret = recv(sfd, &train_to_client, sizeof(train_t), 0);  
                if(ret == 0){                                               
                    //服务器崩溃，退出                                      
                    return -1;                                              
                }                                                           

                //接收服务器的消息                                          
                memcpy(&msg, train_to_client.buf, 1024);                    
printf("type %c\n",msg.msg_type);
                if(msg.msg_type == 'f'){                                    
                    printf("before down\n");                                
                    downloadfile(sfd, train_to_server, train_to_client);    
                }                                                           
                if(msg.msg_type == 't'){                                    
                    printf("before up\n");                                  
                    uploadfile(sfd, train_to_server);                       
                }                                                           
                if(msg.msg_type == 'm'){                                    
                    printf("information\n");
                    printf("%s\n",msg.buf);
                }                                                           
                if(msg.msg_type == 's'){                                    
                    printf("short\n");                                      
                    printf("%s\n",msg.buf);                                 
                }                                                           
                if(msg.msg_type == 'u'){                                    
                    printf("upload success\n");                                      
                    //printf("%s\n",msg.buf);                                 
                }                                                           
            }                                                               
        }                                                                   
        /* } */                                                             
    }         
    close(sfd);                                                                    
    return 0;   
}               
int downloadfile(int sfd, train_t train_to_server, train_t train_to_client){

    msg_t df_msg;
    command_t df_cmd;
    memcpy(&df_msg, train_to_server.buf, sizeof(df_msg));
    memcpy(&df_cmd, df_msg.buf, sizeof(df_cmd));

    int recvNum = 0;
    //创建同名文件
    int fd = open(df_cmd.command_content[1], O_RDWR|O_CREAT, 0666);

    off_t fileSize = train_to_client.data_len;//文件大小
    off_t recvLen = atoi(df_cmd.command_content[2]);//已接收大小
    lseek(fd, recvLen, SEEK_SET);//偏移指针，断点续传

    //float rate = 0;//下载进度

    struct timeval begin, end;
    memset(&begin, 0, sizeof(begin));
    memset(&end, 0, sizeof(end));

    gettimeofday(&begin, NULL);

    //零拷贝 2.splice
    //从接收缓冲区直接拷贝到内核态缓冲区
    int newFd[2];
    pipe(newFd);

    while(recvLen < fileSize){
        recvNum = splice(sfd, 0, newFd[1], 0, 128, 0);
        recvNum = splice(newFd[0], 0, fd, 0, recvNum, 0);
        recvLen += recvNum;
    }
    gettimeofday(&end, NULL);
    printf("cost time = %ld\n", (end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
    return 0;
}
int uploadfile(int sfd, train_t train_to_server){
    msg_t df_msg;
    command_t df_cmd;
    memcpy(&df_msg, train_to_server.buf, sizeof(df_msg));
    memcpy(&df_cmd, df_msg.buf, sizeof(df_cmd));
    int fd = open(df_cmd.command_content[1], O_RDWR);
    struct stat fileInfo;                                                                                                
    bzero(&fileInfo, sizeof(fileInfo));
    //获取文件长度
    fstat(fd, &fileInfo);
    //零拷贝3. splice
    //ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags);
    int pipefd[2];
    pipe(pipefd);

    printf("before splice\n");


    int sendLen = 0;
    while(sendLen < fileInfo.st_size){
        //splice可以限制传输速率
        int ret = splice(fd, 0, pipefd[1], 0, 128, 0);
        ret = splice(pipefd[0], 0, sfd, 0, ret, 0);
        sendLen += ret;
    }
    printf("upload success\n");
    return 0;
}

