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

    Truck_t truck;  //缓冲区
    //用户登录
    if (!user_login(fd_server, &truck)) {
        //登录失败
        printf("Login falied, user_name or user_passwd is error!\n");
        return -1;
    }
    //登录成功
    printf("Login success!\n");


    //从stdin中读取命令，发给服务器
    char line[128] = "";
    Cmd_t cmd;
    while (1) {
        memset(&truck, 0, sizeof(truck));
        memset(&cmd, 0, sizeof(Cmd_t));
        memset(line, 0, sizeof(line));

        //读取命令
        read(STDIN_FILENO, line, sizeof(line));
        line[strlen(line) - 1] = '\0';

        //如果是quit命令，退出程序
        if (!strcmp(line, "quit")) {
            exit(1); 
        }

        //格式化这行数据，并存入cmd
        init_cmd(line, &cmd);

        //将cmd打包放入小货车, 发送给服务器
        memcpy(truck._data, &cmd, sizeof(cmd));
        truck._data_len = sizeof(Cmd_t);
        send(fd_server, &truck, sizeof(int) + truck._data_len, 0);

        //等待服务器返回数据
        system("clear");
        if (!strncmp("ls", cmd._cmd[0], 2)) {
            while (1) {
                recv(fd_server, &truck._data_len, sizeof(int), 0);
                if (0 == truck._data_len) { //收到0，命令结束
                    break;
                }
                recv(fd_server, truck._data, truck._data_len, MSG_WAITALL);
                printf("%s\n", truck._data);
            }
        }
        else if (!strncmp("puts", cmd._cmd[0], 4)) {
            //上传文件
            int ret = -1;

            //检查文件是否存在，且是否是常规文件
            off_t filesize = 0;
            struct stat st;
            stat(cmd._cmd[1], &st);
            filesize = st.st_size;
            printf("filesize = %ld\n", filesize);

            //如果文件不是常规文件，将文件大小设为0
            if (filesize && S_IFREG != (st.st_mode & S_IFMT)) {
                filesize = 0;
            }
            printf("filesize = %ld\n", filesize);
            //发送文件大小，让服务器选择接收方式
            send(fd_server, &filesize, sizeof(int), 0);

            if (0 == filesize) {
                //没找着这个常规文件
                printf("Not found the file!\n");
                return -1;
            }
            else if (filesize > HUNDRED_MEGABYTE) {
                ret = send_file_sendfile(fd_server, cmd._cmd[1], filesize); //大于100M, 用零拷贝接口
            }
            else {
                printf("send_file_truck\n");
                ret = send_file_truck(fd_server, cmd._cmd[1]);//用普通方式发送
            }

            //判断传输结果
            if (-2 == ret) {
                //服务器异常断开, 退出
                printf("server erupt!\n");
                return -1;
            }
            //传输完成，接收传输结果
            recv(fd_server, &truck._data_len, sizeof(int), 0);
            recv(fd_server, truck._data, truck._data_len, MSG_WAITALL);
            printf("%s\n", truck._data);
        }
        else if (!strncmp("gets", cmd._cmd[0], 4)) {
            //下载文件
            int ret = -1;

            //先接文件大小
            int filesize = 0;
            recv(fd_server, &filesize, sizeof(int), 0);
            printf("filesize = %d\n", filesize);

            if (0 == filesize) {
                //文件不存在
                printf("Not found the file!\n");
                continue;
            }
            else if (filesize > HUNDRED_MEGABYTE * 10) {
                ret = recv_file_mmap(fd_server, cmd._cmd[1], filesize);
            }
            else {
                ret = recv_file_truck(fd_server, cmd._cmd[1]);
            }

            //判断传输结果
            if (-2 == ret) {
                //服务器异常断开
                printf("server erupt!\n");
                return -1;
            }
            //传输完成，接收传输结果
            recv(fd_server, &truck._data_len, sizeof(int), 0);
            recv(fd_server, truck._data, truck._data_len, MSG_WAITALL);
            printf("%s\n", truck._data);
        }
        else {
            //其他命令
            //先接命令结果长度，后接命令结果
            recv(fd_server, &truck._data_len, sizeof(int), 0);
            recv(fd_server, truck._data, truck._data_len, 0);
            printf("%s\n", truck._data);
        }
    }
    return 0;
}

//将line分割，存入cmd
void init_cmd(char *line, pCmd_t pcmd)
{
    //使用strtok将line拆分
    char *token;
    const char s[] = {' ', '\n'};

    //首次使用strtok时，需传入待分割的字符串和分隔符集合
    //之后再调用，第一个参数设为NULL，表示从继续上次的位置分割
    token = strtok(line, s);
    while (NULL != token) {
        strcpy(pcmd->_cmd[pcmd->_argc++], token);
        token = strtok(NULL, s);
    }
}

//打印命令
void print_cmd(pCmd_t pcmd)
{
    printf("cmd[%d]: ", pcmd->_argc);
    for (int i = 0; i < pcmd->_argc; ++i) {
        printf("%s ", pcmd->_cmd[i]);
    }
    printf("\n");
}
