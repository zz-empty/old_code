#include "../include/head.h"
#include "../include/func.h"

int user_registration(int fd){
    train_t train;
    memset(&train,0,sizeof(train));
    msg_t msg;
    memset(&msg,0,sizeof(msg));
    userinfo_t userinfo;
    memset(&userinfo,0,sizeof(userinfo));

    char username[20] = {0};
    char * passwd = (char *)calloc(20,1);
    char salt[16] = {0};
    char salt1[16] = {0};
    char cryptpasswd[128] = {0};
    char cryptpasswd1[128] = {0};
    char result[32] = {0};

    while(1){
        memset(&train,0,sizeof(train));
        memset(&msg,0,sizeof(msg));
        memset(&userinfo,0,sizeof(userinfo));
        memset(username,0,sizeof(username));
        memset(salt1,0,sizeof(salt1));

        printf("请输入你的用户名：(不超过20位)\n");
        scanf("%s",username);
        msg.msg_from = 'c';
        msg.msg_type = 'r';
        memcpy(msg.buf,username,sizeof(username));
        memcpy(train.buf,&msg,sizeof(msg));
        train.data_len = sizeof(train.buf);
        send(fd,&train,4+train.data_len,0);
        printf("username is %s\n",msg.buf);

        recv(fd,salt1,sizeof(salt1),0);
        printf("salt1 is %s\n",salt1);

        if(!strcmp(salt1,"exist")){
            printf("用户名已存在，请重新输入：\n");
            continue;
        }
        else{
            break;
        }
    }
    strcpy(salt,"$6$");
    strcat(salt,salt1);
    //strcat(salt,"$");
    printf("salt is %s\n",salt);
    printf("username is %s\n",username);
    while(1){
        memset(passwd,0,20);
        memset(cryptpasswd,0,sizeof(cryptpasswd));
        passwd=getpass("请输入密码:(不超过20位)\n");
        strcpy(cryptpasswd,crypt(passwd,salt));
        printf("cryptpasswd is %s\n",cryptpasswd);

        memset(passwd,0,20);
        memset(cryptpasswd1,0,sizeof(cryptpasswd1));
        passwd=getpass("请输入密码:(再次确认)");
        strcpy(cryptpasswd1,crypt(passwd,salt));
        printf("cryptpasswd1 is %s\n",cryptpasswd1);

        if(!strcmp(cryptpasswd1,cryptpasswd)){
            printf("两次密码输入相同\n");
            break;
        }
        else{
            printf("我没出去\n");
            continue;
        }
    }
    printf("我出来了\n");
    /* memcpy(userinfo.username,username,32); */
    /* memcpy(userinfo.salt,salt,16); */
    /* memcpy(userinfo.cryptpasswd,cryptpasswd,128); */
    strcpy(userinfo.username,username);
    strcpy(userinfo.salt,salt);
    strcpy(userinfo.cryptpasswd,cryptpasswd);
    printf("userinfo.username is %s\n",userinfo.username);
    printf("userinfo.salt is %s\n",userinfo.salt);
    printf("userinfo.username is %s\n",userinfo.cryptpasswd);

    send(fd,&userinfo,sizeof(userinfo),0);

    recv(fd,result,sizeof(result),0);
    if(!strcmp(result,"insertsuccess")){
        printf("注册成功\n");
    }else{
        printf("注册失败\n");
    }

    return 0;
}
