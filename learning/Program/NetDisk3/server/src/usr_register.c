#include "head.h"
#include "func.h"
#include "task_queue.h"
#define STR_LEN 8 //定义随机输出的字符串长度

//生成盐值
int generate_salt(char *salt) {
    char str[STR_LEN+1] = "";
    int i,flag;
    srand(time(NULL));//得到随机种子

    for(i = 0; i < STR_LEN; i ++) {
        flag = rand()%3;
        switch(flag) {
        case 0: str[i] = rand()%26 + 'a'; break;
        case 1: str[i] = rand()%26 + 'A'; break;
        case 2: str[i] = rand()%10 + '0'; break;       
        } 
    }
    strcpy(salt, str);
    return 0;
}

//注册, 先查该用户名是否存在
//如果存在就不注册，通知客户端
//如果不存在，就注册
int user_register(socket_t fd_client, pTruck_t pT)
{
    char *cryptpasswd;
    char *query_result = (char*)calloc(128, 1);//查询结果
    char query[256] = "";//查询语句

    Msg_t msg;//客户端发来的
    User_t user_client;//客户端发来的
    User_t user_query;
    memset(&msg, 0, sizeof(Msg_t));
    memset(&user_client, 0, sizeof(User_t));
    memset(&user_query, 0, sizeof(User_t));

    //从小货车中卸货，得到客户端发来的用户信息（用户名和密码）
    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&user_client, msg._buf, sizeof(User_t));
    memcpy(&user_query, &user_client, sizeof(User_t));
    printf("username: %s\n", user_client._username);
    printf("passwd: %s\n", user_client._passwd);

    //根据用户名查询用户表
    sprintf(query, "%s'%s'", "select salt from userinfo where username = ", user_client._username);
    puts(query);
    mysql_query1(query, &query_result);

    //显示查询结果
    puts(query_result);

    //没找到，注册
    if (!strcmp(query_result, "noexist")) {
        //生成随机盐值
        generate_salt(user_query._salt);
        printf("salt: %s\n", user_query._salt);
        //根据盐值和用户密码，生成加密密码
        cryptpasswd = crypt(user_client._passwd, user_query._salt);
        printf("cryptpasswd: %s\n", cryptpasswd);

        //将新用户插入用户表
        sprintf(query, "%s'%s'%s'%s'%s'%s'%s", "insert into userinfo (username, salt, cryptpasswd) values(", user_query._username, ",", user_query._salt, ",", cryptpasswd, ")");    
        puts(query);
        mysql_insert(query);

        //给新用户建立新的文件结构
        //先获取用户的唯一标识, 用户id
        sprintf(query, "select id from userinfo where username ='%s'", user_query._username);
        puts(query);
        mysql_query1(query, &query_result);
        user_query._user_id = atoi(query_result);
        printf("userid = %d\n", user_query._user_id);

        //建立新的用户文件家目录
        sprintf(query, "insert into virtual_file (filename,parent_id,owner_id,type,filesize,md5) values ('%s',0,%d,'d',0,0)", 
                user_query._username, user_query._user_id);
        if (0 == mysql_insert(query)) {
            printf("Home init succeed!\n");
        }

        //注册成功，通知客户端
        puts("register succeed!");
        pT->_data_len = 1;
        send(fd_client, pT, sizeof(int), 0);
        return 1;
    }
    //找到了，通知客户端无法注册
    else {
        //注册失败，通知客户端
        puts("exist, register failed!");
        pT->_data_len = -1;
        send(fd_client, pT, sizeof(int), 0);
        return -1;
    }
}
