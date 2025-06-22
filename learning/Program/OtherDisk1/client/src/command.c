#include "../include/func.h"
#include "../include/md5.h"

int cd(int sfd, train_t train);
int ls(int sfd, train_t train);
int pwd(int sfd, train_t train);
int rm(int sfd, train_t train);
int mymkdir(int sfd, train_t train);
int download(int sfd, pTrain_t train);
int upload(int sfd, pTrain_t ptrain);
int myRm(pCommand_t pCommand,pActive_user_node_t pUserNode,int clientFd);
    
int command(char choice, pTrain_t p, int sfd){
    //将命令编号，用户只需要选择并输入参数即可
    //定义小火车、信息、命令结构体，存储要发送的信息
    msg_t msg;
    command_t command;
    memset(&msg, 0, sizeof(msg));
    memset(&command, 0, sizeof(command));

    msg.msg_from = 'c';
    msg.is_trust = 1;
    //id
    //token


    /* int fd; */

    switch(choice){
    case 0:
        exit(-1);
        break;
    case 1:
        //cd命令
        cd(sfd, *p);
        break;
    case 2:
        //ls命令
        ls(sfd, *p);
        break;
    case 3:
        //pwd命令
        pwd(sfd, *p);
        break;
    case 4:
        //rm命令
        rm(sfd, *p);
        break;
    case 5:
        //mkdir命令
        mymkdir(sfd, *p);
        break;
    case 6:
        //保留命令
        break;
    case 7:
        //保留命令
        break;
    case 8:
        //download命令
        download(sfd, p);
        break;
    case 9:
        //upload命令
        upload(sfd, p);
        break;
    default:
        printf("error! please input again\n");
        //命令选择
    }
    //传出
    //p = &train;
    
    return 0;
}

int cd(int sfd, train_t train){
    msg_t msg;
    command_t command;
    msg.msg_type = 's';//短命令
    command.word_num = 2;//两个参数 cd 路径（暂时只支持3种：家目录、上级目录、下级目录）
    strcpy(command.command_content[0],"cd");
    printf("please input path:\n");
    scanf("%s", command.command_content[1]);
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(train.buf, &msg, sizeof(msg));//信息存储到小火车中
    train.data_len = sizeof(train);
    send(sfd, &train, sizeof(train), 0);
    return 0;
}

int ls(int sfd, train_t train){
    msg_t msg;
    command_t command;
    msg.msg_type = 's';//短命令
    command.word_num = 1;//一个参数 ls
    strcpy(command.command_content[0],"ls");
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(train.buf, &msg, sizeof(msg));//信息存储到小火车中
    train.data_len = sizeof(train);
    send(sfd, &train, sizeof(train), 0);
    return 0;
}

int pwd(int sfd, train_t train){
    msg_t msg;
    command_t command;
    msg.msg_type = 's';//短命令
    command.word_num = 1;//一个参数 pwd
    strcpy(command.command_content[0],"pwd");
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(train.buf, &msg, sizeof(msg));//信息存储到小火车中
    train.data_len = sizeof(train);
    send(sfd, &train, sizeof(train), 0);
    return 0;
}
int rm(int sfd, train_t train){
    msg_t msg;
    command_t command;
    msg.msg_type = 's';//短命令
    command.word_num = 2;//两个参数 rm 文件名
    strcpy(command.command_content[0],"rm");
    printf("please input file name:\n");
    scanf("%s", command.command_content[1]);
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(train.buf, &msg, sizeof(msg));//信息存储到小火车中
    train.data_len = sizeof(train);
    send(sfd, &train, sizeof(train), 0);
    return 0;
}

int mymkdir(int sfd, train_t train){
    msg_t msg;
    command_t command;
    msg.msg_type = 's';//短命令
    command.word_num = 2;//两个参数 mkdir 文件夹名
    strcpy(command.command_content[0],"mkdir");
    printf("please input folder name:\n");
    scanf("%s", command.command_content[1]);
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(train.buf, &msg, sizeof(msg));//信息存储到小火车中
    train.data_len = sizeof(train);
    send(sfd, &train, sizeof(train), 0);
    return 0;
}

int download(int sfd, pTrain_t ptrain){
    msg_t msg;
    command_t command;
    msg.msg_type = 'l';//长命令
    command.word_num = 3;//三个参数 download 文件名 已有长度
    strcpy(command.command_content[0],"download");
    printf("please input file name:\n");
    scanf("%s", command.command_content[1]);
    FILE* fp = fopen(command.command_content[1], "a+");
    sprintf(command.command_content[2], "%ld", ftell(fp));
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(ptrain->buf, &msg, sizeof(msg));//信息存储到小火车中
    ptrain->data_len = sizeof(ptrain->buf);
    send(sfd, ptrain, sizeof(train_t), 0);

    return 0;
}

int upload(int sfd, pTrain_t ptrain){
    msg_t msg;
    command_t command;
    msg.msg_type = 'l';//长命令
    command.word_num = 3;//三个参数 upload 文件名 md5
    strcpy(command.command_content[0],"upload");
    printf("please input file name:\n");
    scanf("%s", command.command_content[1]);
    int fd = open(command.command_content[1], O_RDWR);
    perror("open");
    struct stat fileInfo;                                                                                                
    bzero(&fileInfo, sizeof(fileInfo));
    //获取文件长度
    fstat(fd, &fileInfo);
    ptrain->data_len = fileInfo.st_size;printf("len = %d\n",ptrain->data_len);
    //计算md5值发送给服务器，如果已有该文件可秒传，否则发送该文件
    //int fd = open(command.command_content[1], O_RDONLY);
    //先发送md5
    char md5_str[MD5_STR_LEN + 1];
    Compute_file_md5(command.command_content[1], md5_str);printf("md5 = %s\n",md5_str);

    memcpy(command.command_content[2], md5_str, strlen(md5_str));
    memcpy(msg.buf, &command, sizeof(command));//命令存储到信息中
    memcpy(ptrain->buf, &msg, sizeof(msg));//信息存储到小火车中
    send(sfd, ptrain, sizeof(train_t), 0);
    return 0;
}

