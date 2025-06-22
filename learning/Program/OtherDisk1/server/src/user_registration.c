#include "../include/head.h"
#include "../include/func.h"
#include "../include/mysql_func.h"

int user_registration(int fd,train_t train){
    int ret = 0;
    msg_t msg;
    memset(&msg,0,sizeof(msg));
    userinfo_t userinfo;
    memset(&userinfo,0,sizeof(userinfo));

    char username[20] = {0};
    char salt[16] = {0};
    char *salt1 = (char *)calloc(16,1);
    char query[300] = {0};
    char *query_result = (char *)calloc(128,1);
    char result[32] = {0};

    memcpy(&msg,train.buf,sizeof(train.buf));
    memcpy(username,msg.buf,20);
    printf("username = %s\n",username);
    //调用数据库函数判断username是否存在
    //如果存在
    strcpy(query,"select * from userinfo where username ='");
    sprintf(query, "%s%s%s", query, username, "'");
    mysql_query1(query,&salt1);
    printf("salt1 is %s\n",salt1);

    if(!strcmp(salt1,"noexist")){
        memset(salt1,0,16);
        generate_salt(&salt1);
        printf("generate_salt is %s\n",salt1);
        strcpy(salt,salt1);
        printf("salt is %s\n",salt);
        send(fd,salt,sizeof(salt),0);//如果数据库不存在该用户名，表示可以注册，则将随机产生的盐值发送给客户端

        recv(fd,&userinfo,sizeof(userinfo),0);//将客户端注册好的信息通过结构体传给服务器端，包括用户名，盐值和加密密码
        printf("userinfo.username is %s\n",userinfo.username);
        printf("userinfo.salt is %s\n",userinfo.salt);
        printf("userinfo.cryptpasswd is %s\n",userinfo.cryptpasswd);
        memset(query,0,sizeof(query));
        strcpy(query,"insert into userinfo (username,salt,cryptpasswd) values (");
        sprintf(query, "%s'%s','%s','%s')", query,userinfo.username,userinfo.salt,userinfo.cryptpasswd);
        ret = mysql_insert(query);
        if(0 == ret ){
            strcpy(result,"insertsuccess");
            printf("result is %s\n",result);

            //memset(query_result,0,128);
            memset(query,0,sizeof(query));
            strcpy(query,"select id from userinfo where username ='");
            sprintf(query, "%s%s%s", query, username, "'");
            printf("query is %s\n",query);
            mysql_query2(query,&query_result);
            printf("query_result is %s\n",query_result);
            userinfo.user_id = atoi(query_result);
            printf("userinfo.user_id is %d\n",userinfo.user_id);

            memset(query,0,sizeof(query));
            strcpy(query,"insert into virtual_file (filename,parent_id,owner_id,type,filesize,md5) values (");
            sprintf(query, "%s'%s','1','%d','d','0','0')", query,username,userinfo.user_id);
            ret = mysql_insert(query);
            if(0 == ret ){
                printf("user_home_init success\n");
            }
            send(fd,result,sizeof(result),0);
        }

    }
    else{
        strcpy(salt,"exist");
        send(fd,salt,sizeof(salt),0);
    }

    return 0;
}
