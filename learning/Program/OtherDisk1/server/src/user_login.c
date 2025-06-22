#include "../include/head.h"
#include "../include/func.h"
#include "../include/mysql_func.h"

int user_login(int fd,train_t train,pActive_user_node_t pnode){
    msg_t msg;
    memset(&msg,0,sizeof(msg));
    userinfo_t userinfo;
    memset(&userinfo,0,sizeof(userinfo));

    char username[20] = {0};
    char salt[16] = {0};
    char query[300] = {0};
    char *query_result = (char *)calloc(128,1);
    char result[32] = {0};

    memcpy(&msg,train.buf,sizeof(train.buf));
    memcpy(username,msg.buf,20);
    printf("username is %s\n",username);
    //调用数据库函数判断username是否存在
    //如果不存在
    memset(salt,0,sizeof(salt));
    memset(query,0,sizeof(query));
    memset(&userinfo,0,sizeof(userinfo));
    strcpy(query,"select salt from userinfo where username ='");
    sprintf(query, "%s%s%s", query, username, "'");
    mysql_query1(query,&query_result);
    if(!strcmp(result,"noexist")){//如果用户输入的用户名不存在
        memcpy(userinfo.salt,"noexist",8);
        printf("userinfo.salt is %s\n",userinfo.salt);
        send(fd,&userinfo,sizeof(userinfo),0);
    }
    else{
        memcpy(userinfo.salt,query_result,strlen(query_result)-1);
        printf("userinfo.salt is %s\n",userinfo.salt);
        memset(query_result,0,128);
        strcpy(query,"select cryptpasswd from userinfo where username ='");
        sprintf(query, "%s%s%s", query, username, "'");
        mysql_query1(query,&query_result);
        memcpy(userinfo.cryptpasswd,query_result,strlen(query_result)-1);
        printf("userinfo.cryptpasswd is %s\n",userinfo.cryptpasswd);
        
        memset(query_result,0,128);
        memset(query,0,sizeof(query));
        strcpy(query,"select id from userinfo where username ='");
        sprintf(query, "%s%s%s", query,username, "'");
        printf("query is %s\n",query);
        mysql_query1(query,&query_result);
        printf("query_result is %s\n",query_result);
        userinfo.user_id = atoi(query_result);
        printf("userinfo.user_id is %d\n",userinfo.user_id);

        pnode->connect_fd = fd;
        printf("pnode->connect_fd = %d\n",pnode->connect_fd);
        pnode->user_id = userinfo.user_id;
        printf("pnode->user_id = %d\n",pnode->user_id);

        memset(query_result,0,128);
        memset(query,0,sizeof(query));
        printf("userinfo.user_id is %d\n",userinfo.user_id);
        strcpy(query,"select id from virtual_file where owner_id = ");
        printf("userinfo.user_id is %d\n",userinfo.user_id);
        sprintf(query, "%s%d", query,userinfo.user_id);
        printf("userinfo.user_id is %d\n",userinfo.user_id);
        printf("query is %s\n",query);
        mysql_query1(query,&query_result);
        printf("query_result is %s\n",query_result);
        int cur_path_id  = atoi(query_result);
        printf("cur_path_id is %d\n",cur_path_id);
        pnode->cur_path_id = cur_path_id;
        printf("userinfo.username is %s\n",username);
        memcpy(pnode->cur_path,username,sizeof(username));
        printf("pnode->cur_path is %s\n",pnode->cur_path);

        send(fd,&userinfo,sizeof(userinfo),0);
    }
    recv(fd,result,sizeof(result),0);
    if(!strcmp(result,"loginsuccess")){
        printf("loginsuccess\n");
    }
    return 0;
}
