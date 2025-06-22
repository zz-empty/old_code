#include "head.h"
#include "func.h"

//如果登录成功返回1，失败返回0
int user_login(socket_t fd_server, pTruck_t pT)
{
    //登录验证
    //输入用户名
    printf("请输入用户名：");
    memset(pT, 0, sizeof(Truck_t));
    //发送用户名
    pT->_data_len = scanf("%s", pT->_data);
    send(fd_server, pT, sizeof(int) + pT->_data_len, 0);
    //输入密码
    memset(pT, 0, sizeof(Truck_t));
    char *passwd;
    passwd = getpass("请输入密码：");
    strncpy(pT->_data, passwd, BUF_SIZE);
    //发送密码
    pT->_data_len = strlen(pT->_data);
    send(fd_server, pT, sizeof(int) + pT->_data_len, 0);

    //接收登录结果
    recv(fd_server, &pT->_data_len, sizeof(int), 0);

    //!= -1登录成功, 返回1
    //== -1登录失败, 返回0
    return -1 != pT->_data_len;
}
