#include "head.h"
#include "func.h"


int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2); 

#if 1
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
#endif

    //从stdin中读取命令，发给服务器
    char line[128] = "";
    Cmd_t cmd;
    Truck_t truck;//小货车，传输数据
    while (1) {
        memset(&truck, 0, sizeof(truck));
        memset(&cmd, 0, sizeof(Cmd_t));
        memset(line, 0, sizeof(line));

        //从标准输入中读取命令
        read(STDIN_FILENO, line, sizeof(line));
        line[strlen(line) - 1] = '\0';

        //格式化这行数据，并存入cmd
        init_cmd(line, &cmd);
        //判断命令是否合法
        if (-1 == cmd_check(&cmd)) {
            printf("the cmd is illegal!\n");
            continue;
        }
        print_cmd(&cmd);
        //将cmd打包放入小货车
        memcpy(truck._data, &cmd, sizeof(cmd));

        //将命令发送给服务器
        truck._data_len = sizeof(Cmd_t);
        send(fd_server, &truck._data_len, sizeof(int), 0);
        sendn(fd_server, truck._data, truck._data_len);

        //等待服务器返回数据
        if (!strncmp("cd", cmd._cmd[0], 2)) {
            system("clear");
            //先接长度，后接数据
            recv(fd_server, &truck._data_len, sizeof(int), 0);
            recvn(fd_server, truck._data, truck._data_len);
            printf("%s\n", truck._data);
        }
        else if (!strncmp("pwd", cmd._cmd[0], 3)) {
            system("clear");
            //先接长度，后接数据
            recv(fd_server, &truck._data_len, sizeof(int), 0);
            recvn(fd_server, truck._data, truck._data_len);
            printf("%s\n", truck._data);
        }
        else if (!strncmp("rm", cmd._cmd[0], 2)) {
            system("clear");
            //先接长度，后接数据
            recv(fd_server, &truck._data_len, sizeof(int), 0);
            recvn(fd_server, truck._data, truck._data_len);
            printf("%s\n", truck._data);
        }
        else if (!strncmp("ls", cmd._cmd[0], 2)) {
            system("clear");
            //先接长度，后接数据
            while (1) {
                recv(fd_server, &truck._data_len, sizeof(int), 0);
                /* printf("data_len: %d\n", truck._data_len); */
                if (0 == truck._data_len) {
                    break;
                }
                recvn(fd_server, truck._data, truck._data_len);
                printf("%s\n", truck._data);
            }
        }
        else if (!strncmp("puts", cmd._cmd[0], 4)) {
            system("clear");
            //上传文件
            if (0 == upload(fd_server, cmd._cmd[1])) {
                printf("file [%s] upload success!\n", cmd._cmd[1]);
            } 
            else {
                printf("file [%s] upload failed!\n", cmd._cmd[1]);
            }
        }
        else if (!strncmp("gets", cmd._cmd[0], 4)) {
            system("clear");
            //下载文件
            if (0 == download(fd_server, cmd._cmd[1])) {
                printf("file [%s] download success!\n", cmd._cmd[1]);
            }
            else {
                printf("file [%s] download failed!\n", cmd._cmd[1]);
            }
        }
    }
    return 0;
}
