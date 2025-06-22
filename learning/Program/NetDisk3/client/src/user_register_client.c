#include "head.h"
#include "func.h"

int user_register(socket_t fd_server)
{
    Truck_t truck;
    memset(&truck, 0, sizeof(Truck_t));
    Msg_t msg;
    memset(&msg, 0, sizeof(Msg_t));
    Usr_t usr;
    memset(&usr, 0, sizeof(Usr_t));

    //录入用户名
    printf("请输入用户名：");
    scanf("%s", usr._username);
    //录入密码
    char *passwd;
    passwd = getpass("请输入密码：");
    strncpy(usr._passwd, passwd, PASSWD_SIZE);

    //发送
    msg._type = 'r';//登录信息类型
    memcpy(msg._buf, &usr, sizeof(Usr_t));//将用户打包进消息
    memcpy(truck._data, &msg, sizeof(Msg_t));//将消息打包进小货车
    truck._data_len = sizeof(Msg_t);
    send(fd_server, &truck, sizeof(int) + truck._data_len, 0);//发车

    //接收登录结果
    recv(fd_server, &truck._data_len, sizeof(int), 0);

    if (1 == truck._data_len) {
        printf("注册成功！\n");
        return 0;
    }
    else {
        printf("注册失败, 已有此用户！\n");
    }
    return -1;
}

