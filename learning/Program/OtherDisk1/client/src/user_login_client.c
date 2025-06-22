#include "../include/head.h"
#include "../include/func.h"

int user_login(int fd)//客户端与服务器端通信的文件描述符
{
    train_t train;
    memset(&train,0,sizeof(train));
    msg_t msg;
    memset(&msg,0,sizeof(msg));
    userinfo_t userinfo;
    memset(&userinfo,0,sizeof(userinfo));

    char username[20] = {0};
    char * passwd = (char *)calloc(20,1);
    char salt[16] = {0};
    char cryptpasswd[128] = {0};
    char cryptpasswd1[128] = {0};
    char result[32] = {0};

    while(1){
        memset(&train,0,sizeof(train));
        memset(&msg,0,sizeof(msg));
        memset(&userinfo,0,sizeof(userinfo));
        memset(username,0,sizeof(username));

        printf("请输入你的用户名：(不超过20位)\n");
        scanf("%s",username);
        memcpy(msg.buf,username,sizeof(username));
        msg.msg_from = 'c';
        msg.msg_type = 'i';
        memcpy(train.buf,&msg,sizeof(msg));
        train.data_len = sizeof(train.buf);
        send(fd,&train,4+train.data_len,0);
        printf("msg.buf is %s\n",msg.buf);

        recv(fd,&userinfo,sizeof(userinfo),0);
        printf("userinfo.salt is %s\n",userinfo.salt);
        printf("userinfo.cryptpasswd is %s\n",userinfo.cryptpasswd);
        if(!strcmp(userinfo.salt,"noexist")){
            printf("用户名不存在，请重新输入：\n");
            continue;
        }
        else{
            strcpy(salt,userinfo.salt);
            strcpy(cryptpasswd,userinfo.cryptpasswd);
            printf("salt is %s$\n",salt);
            printf("cryptpasswd is %s\n",cryptpasswd);
            break;
        }
    }
    while(1){
        memset(cryptpasswd1,0,sizeof(cryptpasswd1));
        passwd=getpass("请输入密码:(不超过20位)");
        strcpy(cryptpasswd1,crypt(passwd,salt));
        printf("before cmp,cryptpasswd is %s&\n",cryptpasswd);
        printf("before cmp,cryptpasswd1 is %s&\n",cryptpasswd1);
        if(!strcmp(cryptpasswd,cryptpasswd1)){
            printf("密码正确，正在登陆......\n");
            memset(result,0,sizeof(result));
            strcpy(result,"loginsuccess");
            send(fd,result,sizeof(result),0);
            break;
        }
        else{
            printf("密码错误，请重新输入：\n");
            continue;
        }
    }
    return 0;
}

