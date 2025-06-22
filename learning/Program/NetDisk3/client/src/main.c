#include "head.h"
#include "func.h"


int main(int argc, char *argv[])
{
    //命令行参数：配置文件路径
    ARGS_CHECK(argc, 2); 

    //拿到服务器ip和port
    char ip_server[16] = "";
    char port_server[5] = "";
    conf_get(argv[1], ip_server, port_server);

    //连接服务器
    socket_t fd_server = tcp_connect(ip_server, atoi(port_server));
    if (-1 == fd_server) {
        perror("socket_server");
        exit(-1);
    }

    printf("main pid = %d\n", getpid());
    Truck_t truck;//发送接收缓冲区

    //用户登录
    while (1) {
        printf("1-登录\n2-注册\n3-退出\n请选择：");

        int choose;
        scanf("%d", &choose);
        if (1 == choose) {
            //登录
            if (0 == user_login(fd_server)) {
                system("clear");
                break;
            }
            else {
                printf("登录失败，用户名或密码错误!\n");
                continue;
            }    
        }
        else if (2 == choose) {
            //注册
            if (0 == user_register(fd_server)) {
                printf("注册成功！\n");
            }
            else {
                printf("注册失败，用户名已存在\n");
            }
            continue;
        }
        else if (3 == choose) {
            //退出
            close(fd_server);
            exit(0);
        }
        else {
            printf("没有这个选项，请重新选择！\n");
        }
    }

    //登录成功, 发送命令
    printf("登录成功！\n");
    command_client(fd_server, &truck);
    return 0;
}

