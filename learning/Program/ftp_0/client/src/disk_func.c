#include "head.h"
#include "func.h"

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
    printf("cmd: ");
    for (int i = 0; i < pcmd->_argc; ++i) {
        printf("%s ", pcmd->_cmd[i]);
    }
    printf("\n");
}

//检查命令是否合法
int cmd_check(pCmd_t pcmd) 
{
    char tmp[64] = "";
    strncpy(tmp, pcmd->_cmd[0], 64);
    if (!strcmp(tmp, "cd") || 
        !strcmp(tmp, "ls") ||
        !strcmp(tmp, "pwd") ||
        !strcmp(tmp, "rm") ||
        !strcmp(tmp, "puts") ||
        !strcmp(tmp, "gets") ||
        !strcmp(tmp, "mkdir")) {
        return 0;
    } 
    else {
        return -1;
    }
}

#if 0
//从fd中接收len长度的数据，放入buf_recv
int recvn(int fd_recv, char *buf_recv, int len)
{
    int cnt = 0;
    int ret = 0;
    while (cnt < len) {
        ret = recv(fd_recv, &buf_recv[cnt], len - cnt, 0);
        if (0 == ret) {
            break;
        }
        cnt += ret;
    }
    buf_recv[cnt] = '\0';
    return cnt;
}

//向fd，发送len长度的数据，从buf_send缓冲区
int sendn(int fd_send, char *buf_send, int len)
{
    int cnt = 0;
    int ret = 0;
    while (cnt < len) {
        ret = send(fd_send, &buf_send[cnt], len - cnt, 0);
        cnt += ret;
    }
    return cnt;
}

//从fd中读取len长度的数据
int readn(int fd_read, char *buf_read, int len)
{
    int cnt = 0;
    int ret = 0;
    while (cnt < len) {
        ret = read(fd_read, buf_read + cnt, len - cnt);
        if (0 == ret) {
            break;
        }
        cnt += ret;
    }
    buf_read[cnt] = '\0';
    return cnt;
}

//向fd中写入len长度的数据
int writen(int fd_write, char *buf_write, int len)
{
    int cnt = 0;
    int ret = 0;
    while (cnt < len) {
        ret = write(fd_write, buf_write + cnt, len - cnt);
        cnt += ret;
    }
    return cnt;
}
#endif

//上传文件
int upload(int fd_socket, char *filename)
{
    int ret = -1;
    //定义一个小货车，用来传输文件
    Truck_t truck;
    memset(&truck, 0, sizeof(Truck_t));

    //根据文件名打开传输文件
    int fd_file = open(filename, O_RDONLY);
    EXIT_CHECK(fd_file, -1, "open");

#if 0
    //发文件大小
    struct stat file_info;
    memset(&file_info, 0, sizeof(file_info));
    fstat(fd_file, &file_info);

    truck._data_len = sizeof(file_info.st_size);
    memcpy(truck._data, &file_info.st_size, truck._data_len);
    ret = send(fd_socket, &truck, sizeof(int) + truck._data_len, 0);
    EXIT_CHECK(ret, -1, "send_filesize");
#endif

    //发文件内容
    while (1) {
        memset(truck._data, 0, sizeof(truck._data));

        //读取文件
        truck._data_len = readn(fd_file, truck._data, BUF_SIZE);
        if (0 == truck._data_len) {
            //传输完成，退出循环
            break;
        }

        //发送
        ret = send(fd_socket, &truck, sizeof(int) + truck._data_len, 0);
        if (-1 == ret) {
            //服务器异常断开，退出循环
            printf("server already break!\n");
            break;
        }
    }

    //传输完成，通知fd
    truck._data_len = 0;
    send(fd_socket, &truck._data_len, sizeof(int), 0);

    //关闭传输文件
    close(fd_file);
    return 0;
}

//下载文件
int download(int fd_socket, char *filename)
{
    //打开或创建一个文件
    int fd_file = open(filename, O_WRONLY | O_CREAT, 0600);
    EXIT_CHECK(fd_file, -1, "open");

    /* //接收文件大小 */
    /* int filesize = 0; */
    /* recv(fd_socket, &filesize, sizeof(int), 0); */
    /* printf("filesize: %d", filesize); */

    //接收文件内容
    Truck_t truck;
    while (1) {
        memset(&truck, 0, sizeof(truck));
        //接收数据长度
        recv(fd_socket, &truck._data_len, sizeof(truck._data_len), 0);
        if (0 == truck._data_len) {
            //文件传输完毕
            break;
        }
        //接收数据内容
        recv(fd_socket, truck._data, truck._data_len, MSG_WAITALL);
        write(fd_file, truck._data, truck._data_len);
    }

    close(fd_file);
    return 0;
}
