#include "head.h"
#include "func.h"
#include <crypt.h>
#include <shadow.h>

//从加密密码中获取盐值                                                                                                                                     
void getsalt(char *salt, char *passwd)
{
    int i = 0;//定位第三个$符号后面的字符串
    int j = 0;//计算$的数量
    for (i = 0, j = 0; passwd[i] && j != 3; ++i) {
        if ('$' == passwd[i]) {
            j++;
        }   
    }   

    strncpy(salt, passwd, i - 1); 
}

//验证客户端的用户名和密码
int login_varify(socket_t fd, pTruck_t pT)
{
    char user_name[128] = "";
    char user_passwd[128] = "";
    //接收用户名
    memset(pT, 0, sizeof(Truck_t));
    recv(fd, &pT->_data_len, sizeof(int), 0);
    recv(fd, pT->_data, pT->_data_len, 0);
    /* printf("recv_username: %s\n", truck._data); */
    strncpy(user_name, pT->_data, sizeof(user_name) - 1);

    //接收密码
    memset(pT, 0, sizeof(Truck_t));
    recv(fd, &pT->_data_len, sizeof(int), 0);
    recv(fd, pT->_data, pT->_data_len, 0);
    /* printf("recv_passwd: %s\n", truck._data); */
    strncpy(user_passwd, pT->_data, sizeof(user_passwd) - 1);

    //验证
    //检查用户是否存在
    struct spwd *sp = NULL;    //用来获取/etc/shadow中的加密密码
    char salt[512] = ""; //用来获取用户的盐值

    sp = getspnam(user_name);
    if (NULL == sp) {
        printf("[%s] login failed, user_name error!\n", user_name);
        return -1;
    }
    else {
        //获取salt
        getsalt(salt, sp->sp_pwdp);
        //比对
        if (!strcmp(sp->sp_pwdp, crypt(user_passwd, salt))) {
            printf("[%s] login success!\n", user_name);
            return 0;
        }
        else {
            printf("[%s] login failed, user_passwd error!\n", user_name);
            return -1;
        }
    }
}
