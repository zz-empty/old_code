#include "head.h"
#include "func.h"

int get_filesize(char *filename); //获取文件大小
int recv_file_small(socket_t fd_socket, char *filename); //小于100M的接收方式
int recv_file_big(socket_t fd_socket, char *filename, off_t filesize); //大于100M，用mmap接收
int send_file_big(socket_t fd_socket, char *filename, int filesize); //文件大于100M, 用sendfile发送文件
int send_file_small(socket_t fd_socket, char *filename);//小于100M的发送方式

void init_cmd(char *line, pCmd_t pcmd); //将line分割，存入cmd
void print_cmd(pCmd_t pcmd); //打印命令


//客户端发送命令，接收命令结果
int command_client(socket_t fd_server, pTruck_t pT)
{
    //从stdin中读取命令，发给服务器
    char line[128] = "";
    Cmd_t cmd;

    while (1) {
        memset(pT, 0, sizeof(Truck_t));
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
        memcpy(pT->_data, &cmd, sizeof(cmd));
        pT->_data_len = sizeof(Cmd_t);
        send(fd_server, pT, sizeof(int) + pT->_data_len, 0);

        //等待服务器返回数据
        system("clear");
        if (!strncmp("ls", cmd._cmd[0], 2)) {
            while (1) {
                recv(fd_server, &pT->_data_len, sizeof(int), 0);
                if (0 == pT->_data_len) { //收到0，命令结束
                    break;
                }
                recv(fd_server, pT->_data, pT->_data_len, MSG_WAITALL);
                printf("%s\n", pT->_data);
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

            //根据文件大小选择
            if (0 == filesize) {
                //没找着这个常规文件
                printf("Not found the file!\n");
                return -1;
            }
            else if (filesize > HUNDRED_MEGABYTE) {
                ret = send_file_big(fd_server, cmd._cmd[1], filesize); //大于100M, 用零拷贝接口
            }
            else {
                printf("send_file_truck\n");
                ret = send_file_small(fd_server, cmd._cmd[1]);//用普通方式发送
            }

            //判断传输结果
            if (-2 == ret) {
                //服务器异常断开, 退出
                printf("server erupt!\n");
                return -1;
            }
            //传输完成，接收传输结果
            recv(fd_server, &pT->_data_len, sizeof(int), 0);
            recv(fd_server, pT->_data, pT->_data_len, MSG_WAITALL);
            printf("%s\n", pT->_data);
        }
        else if (!strncmp("gets", cmd._cmd[0], 4)) {
            //下载文件
            int ret = -1;

            //先接文件大小
            int filesize = 0;
            recv(fd_server, &filesize, sizeof(int), 0);
            printf("filesize = %d\n", filesize);

            //根据文件大小选择
            if (0 == filesize) {
                //文件不存在
                printf("Not found the file!\n");
                continue;
            }
            else if (filesize > HUNDRED_MEGABYTE * 10) {
                ret = recv_file_big(fd_server, cmd._cmd[1], filesize);
            }
            else {
                ret = recv_file_small(fd_server, cmd._cmd[1]);
            }

            //判断传输结果
            if (-2 == ret) {
                //服务器异常断开
                printf("server erupt!\n");
                return -1;
            }
            //传输完成，接收传输结果
            recv(fd_server, &pT->_data_len, sizeof(int), 0);
            recv(fd_server, pT->_data, pT->_data_len, MSG_WAITALL);
            printf("%s\n", pT->_data);
        }
        else {
            //其他命令
            //先接命令结果长度，后接命令结果
            recv(fd_server, &pT->_data_len, sizeof(int), 0);
            recv(fd_server, pT->_data, pT->_data_len, 0);
            printf("%s\n", pT->_data);
        }
    }
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
