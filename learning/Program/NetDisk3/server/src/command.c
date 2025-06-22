#include "head.h"
#include "func.h"

int get_filesize(char *filename); //获取文件大小
int send_file_small(socket_t fd_client, char *filename); //小于100M的发送方式
int send_file_big(socket_t fd_client, char *filename, off_t filesize); //文件大于100M, 用sendfile发送文件
int recv_file_small(socket_t fd_socket, char *filename); //小于100M的接收方式
int recv_file_big(socket_t fd_socket, char *filename, off_t filesize); //大于100M，用mmap接收

//打印命令
void print_cmd(pCmd_t pcmd)
{
    printf("---cmd[%d]: ", pcmd->_argc);
    for (int i = 0; i < pcmd->_argc; ++i) {
        printf("%s ", pcmd->_cmd[i]);
    }
    printf("\n");
}

//将文件类型从int转成char*
void file_type(mode_t mode, char *type)
{
    if (S_ISREG(mode)) {
        strncpy(type, "-", 1);
    }
    else if (S_ISDIR(mode)) {
        strncpy(type, "d", 1);
    }
    else if (S_ISFIFO(mode)) {
        strncpy(type, "p", 1);
    }
    else {
        strncpy(type, "o", 1);
    }
}

int do_ls(socket_t fd_client, pTruck_t pT)
{
    //得到一个当前工作目录的目录流
    DIR *dirp = opendir("./");
    if (NULL == dirp) {
        int flag = -1;  //目录流打开失败，发送-1作为标志
        send(fd_client, &flag, sizeof(flag), 0);
        return -1;
    }

    //拼接目录下的每一条文件信息，发送给客户端
    //文件类型，文件名，文件大小
    struct dirent *dir_info;    //目录项
    struct stat fileinfo;  //文件详细信息
    while ((dir_info = readdir(dirp)) != NULL) {
        if (!strncmp(".", dir_info->d_name, 1) || !strncmp("..", dir_info->d_name, 2)) {
            continue;
        }

        memset(pT, 0, sizeof(Truck_t));
        memset(&fileinfo, 0, sizeof(fileinfo));

        //获取文件类型
        char type[1] = "";
        stat(dir_info->d_name, &fileinfo);
        file_type(fileinfo.st_mode, type);

        //拼接此文件信息, 发送
        sprintf(pT->_data, "%-2s%-20s   %10ldB", type, dir_info->d_name, fileinfo.st_size);
        pT->_data_len = strlen(pT->_data);
        send(fd_client, pT, sizeof(int) + pT->_data_len, 0);
    }

    //此目录文件已读完, 发送0作为标志
    pT->_data_len = 0;
    send(fd_client, pT, sizeof(int), 0);

    closedir(dirp);
    return 0;
}

int do_pwd(socket_t fd_client, pTruck_t pT)
{
    //获取当前工作目录
    memset(pT, 0, sizeof(Truck_t));
    getcwd(pT->_data, BUF_SIZE);

    //回应客户端
    pT->_data_len = sizeof(pT->_data);
    send(fd_client, pT, sizeof(int) + pT->_data_len, 0);
    return 0;
}

int do_cd(socket_t fd_client, pTruck_t pT)
{
    Msg_t msg;
    Cmd_t cmd;
    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&cmd, msg._buf, sizeof(Cmd_t));
    //拿到目标目录
    strcpy(pT->_data, cmd._cmd[1]);
    //切换目录
    chdir(pT->_data);

    //回应客户端
    getcwd(pT->_data, BUF_SIZE);
    pT->_data_len = sizeof(pT->_data);
    send(fd_client, pT, sizeof(int) + pT->_data_len, 0);
    return 0;
}

int do_rm(socket_t fd_client, pTruck_t pT)
{
    Msg_t msg;
    Cmd_t cmd;
    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&cmd, msg._buf, sizeof(Cmd_t));

    //查看文件是否存在
    DIR *dirp = opendir("./");
    struct dirent *dir_cur;
    while ((dir_cur = readdir(dirp)) != NULL) {
        if (!strcmp(dir_cur->d_name, cmd._cmd[1])) {  //找到了
            break;
        }
    }
    closedir(dirp);

    if (dir_cur) {
        //文件存在，删除成功
        sprintf(pT->_data, "rm -rf %s", cmd._cmd[1]);
        system(pT->_data);
        sprintf(pT->_data, "file [%s] removed success!", cmd._cmd[1]);
    }
    else {
        //文件不存在，删除失败
        sprintf(pT->_data, "file [%s] removed failed!", cmd._cmd[1]);
    }
    //回应客户端
    pT->_data_len = sizeof(pT->_data);
    send(fd_client, pT, sizeof(int) + pT->_data_len, 0);
    return 0;
}

int do_mkdir(socket_t fd_client, pTruck_t pT)
{
    Msg_t msg;
    Cmd_t cmd;
    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&cmd, msg._buf, sizeof(Cmd_t));

    //目录名是文件的第二个参数
    //查看新目录是否存在
    DIR *dirp = opendir("./");
    struct dirent *dir_cur;
    while ((dir_cur = readdir(dirp)) != NULL) {
        if (!strcmp(dir_cur->d_name, cmd._cmd[1])) {
            struct stat st;
            stat(dir_cur->d_name, &st);
            if ((st.st_mode & S_IFMT) == S_IFDIR) {
                //找到了，而且是目录
                break;
            }
        }
    }
    closedir(dirp);
    
    if (NULL == dir_cur) {
        mkdir(cmd._cmd[1], 0775); //创建目录
        sprintf(pT->_data, "create dir [%s] succeed!", cmd._cmd[1]);  //回应客户端, 创建成功
    }
    else {
        //目录已存在, 创建失败
        sprintf(pT->_data, "the [%s] is already exist!", cmd._cmd[1]);
    }
    //回应客户端
    pT->_data_len = sizeof(pT->_data);
    send(fd_client, pT, sizeof(int) + pT->_data_len, 0);

    return 0;
}

int do_puts(socket_t fd_client, pTruck_t pT)
{
    Msg_t msg;
    Cmd_t cmd;
    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&cmd, msg._buf, sizeof(Cmd_t));

    //客户端是上传，服务器是接收
    //文件名是命令的第二个参数
    int ret = -1;

    //接收文件大小，如果=0，退出
    off_t filesize = 0;
    recv(fd_client, &filesize, sizeof(int), 0);
    printf("filesize = %ld\n", filesize);

    if (0 == filesize) {
        //文件有问题无法接收，退出
        return -1;
    }
    else if (filesize > HUNDRED_MEGABYTE) {
        ret = recv_file_big(fd_client, cmd._cmd[1], filesize); //大于100M, 用mmap接收
    }
    else {
        ret = recv_file_small(fd_client, cmd._cmd[1]); //用普通方式接收
    }
    

    //判断接收结果
    if (-2 == ret) {
        //客户端异常断开，返回-2
        return -2;
    }
    else if (0 == ret) {
        //正常传输完毕, 通知客户端
        sprintf(pT->_data, "file [%s] upload succeed!", cmd._cmd[1]);
    }
    //回应客户端
    pT->_data_len = sizeof(pT->_data);
    send(fd_client, pT, sizeof(int) + pT->_data_len, 0);
    return 0;
}

int do_gets(socket_t fd_client, pTruck_t pT)
{
    Msg_t msg;
    Cmd_t cmd;
    memcpy(&msg, pT->_data, sizeof(Msg_t));
    memcpy(&cmd, msg._buf, sizeof(Cmd_t));

    //客户端是下载，服务器是发送
    //文件名是命令的第二个参数
    int ret = -1;
    
    //得到文件大小
    off_t filesize = 0;
    struct stat st;
    stat(cmd._cmd[1], &st);
    filesize = st.st_size;

    //文件类型不是常规的，就将文件大小设为0
    if (filesize && S_IFREG != (st.st_mode & S_IFMT)) {
        filesize = 0;
    } 

    //发送文件大小，让客户端选择传输方式
    send(fd_client, &filesize, sizeof(int), 0);

    if (0 == filesize) {
        //没找到，退出
        printf("Not found the file!\n");
        return -1;
    }
    else if (filesize > HUNDRED_MEGABYTE * 10) {
        ret = send_file_big(fd_client, cmd._cmd[1], filesize); //>100M, 用零拷贝接口
    }
    else {
        ret = send_file_small(fd_client, cmd._cmd[1]); //用普通方式发送
    }
    
    //判断传输结果
    if (-2 == ret) {
        //客户端意外断开，返回-2
        return -2;
    }
    else if (0 == ret) {
        //正常传输完毕，通知客户端
        sprintf(pT->_data, "file [%s] download succeed!", cmd._cmd[1]);
        puts(pT->_data);
    }
    //回应客户端
    pT->_data_len = sizeof(pT->_data);
    send(fd_client, pT, sizeof(int) + pT->_data_len, 0);
    return 0;
}
