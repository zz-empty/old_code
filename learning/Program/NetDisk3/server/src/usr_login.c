#include "head.h"
#include "func.h"

//登录， 验证客户端的用户名和密码
int user_login(socket_t fd_client, pTruck_t pT, pActive_user_node_t pN)
{
    char *query_result = (char*)calloc(128, 1);//查询结果
    char query[256] = "";//查询语句
    char salt[256] = "";    //盐值
    char cryptpasswd[256] = ""; //加密密码
    char client_cryptpasswd[256] = "";

    //从小货车中卸货，得到用户发来的用户名和密码
    Msg_t msg;
    User_t user_client;
    memset(&msg, 0, sizeof(Msg_t));
    memset(&user_client, 0, sizeof(User_t));

    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&user_client, msg._buf, sizeof(User_t));
    printf("username: %s, passwd: %s\n", user_client._username, user_client._passwd);

    //根据用户名查询盐值
    sprintf(query, "%s'%s'", "select salt from userinfo where username = ", user_client._username);
    mysql_query1(query, &query_result);


    //没找到，通知客户端
    if (!strcmp(query_result, "noexist")) {
        pT->_data_len = -2;
        send(fd_client, pT, sizeof(int), 0);
        return -1;    
    }

    //找到了，验证密码
    //记录用户盐值
    memcpy(salt, query_result, strlen(query_result) - 1);
    printf("userinfo_salt = %s\n", salt);

    //查询用户加密密码 //记录用户加密密码
    memset(query_result, 0, 128);
    sprintf(query, "select cryptpasswd from userinfo where username = '%s'", user_client._username);
    mysql_query1(query, &query_result);
    memcpy(cryptpasswd, query_result, strlen(query_result) - 1);
    printf("userinfo_cryptpasswd = %s\n", cryptpasswd);

    strcpy(client_cryptpasswd, crypt(user_client._passwd, salt));

    //对比
    if (!strcmp(cryptpasswd, client_cryptpasswd)) {
        //密码一致，登录成功
        puts("login succeed!");
        pT->_data_len = 1;
        send(fd_client, pT, sizeof(int), 0);

        //记录当前用户信息，到用户节点
        pN->_connect_fd = fd_client;

        sprintf(query, "select id from userinfo where username = '%s'", user_client._username);
        mysql_query1(query, &query_result);
        pN->_user_id = atoi(query_result);
        
        sprintf(query, "select pwd from userinfo where username = '%s'", user_client._username);
        mysql_query1(query, &query_result);
        memcpy(pN->_cur_path, query_result, strlen(query_result) - 1);

        sprintf(query, "select parent_id from virtual_file where owner_id = %d", pN->_user_id);
        mysql_query1(query, &query_result);
        pN->_cur_path_id = atoi(query_result);

        return 0;
    }
    else {
        //密码不一致，登录失败
        puts("login failed!");
        pT->_data_len = -1;
        send(fd_client, pT, sizeof(int), 0);
        return -1;
    }
}
