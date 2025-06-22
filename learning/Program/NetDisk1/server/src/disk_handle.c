#include "head.h"
#include "func.h"
#include "task_queue.h"

//静态函数的可见域是本文件
//向客户端发送命令结果
static int do_ls(pSession_t ps);
static int do_pwd(pSession_t ps);
static int do_cd(pSession_t ps, pCmd_t pcmd);
static int do_rm(pSession_t ps, pCmd_t pcmd);
static int do_mkdir(pSession_t ps, pCmd_t pcmd);
static int do_puts(pSession_t ps, pCmd_t pcmd);
static int do_gets(pSession_t ps, pCmd_t pcmd);
//将文件类型从int转成char*
static void file_type(mode_t mode, char *type);


//线程清理函数
void clean_func(void *p)
{
    pTaskQueue_t pQue = (pTaskQueue_t)p;
    pthread_mutex_unlock(&pQue->_mutex);
}

//子线程的具体工作，回应客户端发来的命令
void *child_handle(void *p)
{
    //参数是任务队列
    pTaskQueue_t pQue = (pTaskQueue_t)p;

    pTaskNode_t pCur = NULL;  //定义一个任务节点，用来接收任务
    pSession_t ps = (pSession_t)calloc(1, sizeof(Session_t)); //定义一个通信类型，用来传递客户端套接字和缓冲区
    int data_len = -1;  //数据长度
    Cmd_t cmd; //定义一个命令类型，用来接命令
    int ret = -1;

    while (1) {
        //如果退出标志为1，退出线程
        if (1 == pQue->_flag) {
            printf("thread exit!\n");
            free(ps);
            ps = NULL;
            pthread_exit(NULL);
        }

        //从任务队列中取一个任务
        pthread_mutex_lock(&pQue->_mutex);
        pthread_cleanup_push(clean_func, pQue);//线程清理
        if (0 == pQue->_size) {
            pthread_cond_wait(&pQue->_cond, &pQue->_mutex);//等待任务
        }
        get_TaskNode(pQue, &pCur);//得到任务
        pthread_mutex_unlock(&pQue->_mutex);

        //处理任务
        ps->_sess_fd = pCur->_clifd;//设置客户端套接字
        printf("client connected...\n");
        while (1) {
            memset(ps->_sess_buf, 0, BUF_SIZE);
            memset(&cmd, 0, sizeof(Cmd_t));

            //先接收数据长度
            ret = recv(ps->_sess_fd, &data_len, sizeof(data_len), 0);
            if (0 == ret || 0 == data_len) {
                //对端已断开
                close(ps->_sess_fd);
                printf("client exit!\n");
                break;//此次任务结束，退出循环
            }

            //再接收具体的数据
            recv(ps->_sess_fd, ps->_sess_buf, data_len, 0);
            //从接收缓冲区中读取命令
            memcpy(&cmd, ps->_sess_buf, sizeof(Cmd_t));
            print_cmd(&cmd);
            //判断是什么命令
            if (!strcmp("cd", cmd._cmd[0])) {
                do_cd(ps, &cmd);
            }
            else if (!strcmp("pwd", cmd._cmd[0])) {
                do_pwd(ps);
            }
            else if (!strcmp("ls", cmd._cmd[0])) {
                do_ls(ps);
            }
            else if (!strcmp("rm", cmd._cmd[0])) {
                do_rm(ps, &cmd);
            }
            else if (!strcmp("mkdir", cmd._cmd[0])) {
                do_mkdir(ps, &cmd);
            }
            else if (!strcmp("puts", cmd._cmd[0])) {
                do_puts(ps, &cmd);
            }
            else if (!strcmp("gets", cmd._cmd[0])) {
                do_gets(ps, &cmd);
            }
            else {
                //非法命令
                continue;
            }
        }
        pthread_cleanup_pop(1);//线程清理
    }
}

//将文件类型从int转成char*
static void file_type(mode_t mode, char *type)
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

static int do_ls(pSession_t ps)
{
    //生成目录流
    DIR *dirp = opendir("./");

    if (NULL == dirp) {
        int flag = -1;  //目录流打开失败，发送-1作为标志
        send(ps->_sess_fd, &flag, sizeof(flag), 0);
        return -1;
    }
    else {
        struct dirent *dir_info;
        int data_len = -1;

        //循环读取目录项
        while ((dir_info = readdir(dirp)) != NULL) {
            if (!strncmp(".", dir_info->d_name, 1) || !strncmp("..", dir_info->d_name, 2)) {
                continue;
            }

            //获取目录项的信息
            struct stat stat_info;
            memset(&stat_info, 0, sizeof(stat_info));
            stat(dir_info->d_name, &stat_info);

            //获取文件类型
            char type[1] = "";
            file_type(stat_info.st_mode, type);

            //拼接此文件信息
            memset(ps->_sess_buf, 0, BUF_SIZE);
            sprintf(ps->_sess_buf, "%-2s%-20s   %10ldB", type, dir_info->d_name, stat_info.st_size);

            //发送此文件信息
            data_len = strlen(ps->_sess_buf);
            send(ps->_sess_fd, &data_len, sizeof(data_len), 0);//先发数据长度
            send(ps->_sess_fd, ps->_sess_buf, data_len, 0);
        }

        //此目录文件已读完, 发送0作为标志
        data_len = 0;
        send(ps->_sess_fd, &data_len, sizeof(data_len), 0);
    }

    closedir(dirp);
    return 0;
}

static int do_pwd(pSession_t ps)
{
    //获取当前工作目录
    memset(ps->_sess_buf, 0, BUF_SIZE);
    getcwd(ps->_sess_buf, BUF_SIZE);

    //回应客户端
    int data_len = strlen(ps->_sess_buf);
    send(ps->_sess_fd, &data_len, sizeof(int), 0);
    send(ps->_sess_fd, ps->_sess_buf, data_len, 0);
    return 0;
}

static int do_cd(pSession_t ps, pCmd_t pcmd)
{
    //拿到目标目录
    char dir[128] = "";
    strcpy(dir, pcmd->_cmd[1]);
    //切换目录
    chdir(dir);

    //回应客户端
    getcwd(dir, sizeof(dir));
    int data_len = strlen(dir);
    send(ps->_sess_fd, &data_len, sizeof(int), 0);
    send(ps->_sess_fd, dir, data_len, 0);
    return 0;
}

static int do_rm(pSession_t ps, pCmd_t pcmd)
{
    //查看文件是否存在
    DIR *dirp = opendir("./");
    struct dirent *dir_cur;
    while ((dir_cur = readdir(dirp)) != NULL) {
        if (!strcmp(dir_cur->d_name, pcmd->_cmd[1])) {
            break;
        }
    }
    closedir(dirp);

    if (dir_cur) {
        //删除文件
        char cmd[256] = "";
        sprintf(cmd, "rm -rf %s", pcmd->_cmd[1]);
        system(cmd);

        //回应客户端
        sprintf(ps->_sess_buf, "file [%s] removed success!", pcmd->_cmd[1]);
    }
    else {
        //文件不存在
        sprintf(ps->_sess_buf, "file [%s] removed failed!", pcmd->_cmd[1]);
    }
    int data_len = strlen(ps->_sess_buf);
    send(ps->_sess_fd, &data_len, sizeof(int), 0);
    send(ps->_sess_fd, ps->_sess_buf, data_len, 0);
    return 0;
}

static int do_mkdir(pSession_t ps, pCmd_t pcmd)
{
    //查看新目录是否存在
    DIR *dirp = opendir("./");
    struct dirent *dir_cur;
    while ((dir_cur = readdir(dirp)) != NULL) {
        if (!strcmp(dir_cur->d_name, pcmd->_cmd[1]) && S_ISDIR(dir_cur->d_type)) {
            break;
        }
    }
    closedir(dirp);
    
    if (NULL == dir_cur) {
        //创建目录
        mkdir(pcmd->_cmd[1], 0775);

        //回应客户端, 创建成功
        sprintf(ps->_sess_buf, "create dir [%s] succeed!", pcmd->_cmd[1]);
    }
    else {
        //目录已存在, 创建失败
        sprintf(ps->_sess_buf, "the [%s] is already exist!", pcmd->_cmd[1]);
    }
    int data_len = strlen(ps->_sess_buf);
    send(ps->_sess_fd, &data_len, sizeof(int), 0);
    send(ps->_sess_fd, ps->_sess_buf, data_len, 0);

    return 0;
}

static int do_puts(pSession_t ps, pCmd_t pcmd)
{
    //客户端是上传，服务器是下载
    if (0 == download(ps->_sess_fd, pcmd->_cmd[1])) {
        sprintf(ps->_sess_buf, "file [%s] upload succeed!", pcmd->_cmd[1]);
    }
    else {
        sprintf(ps->_sess_buf, "file [%s] upload failed!", pcmd->_cmd[1]);
    }
    int data_len = strlen(ps->_sess_buf);
    send(ps->_sess_fd, &data_len, sizeof(int), 0);
    send(ps->_sess_fd, ps->_sess_buf, data_len, 0);
    return 0;
}

static int do_gets(pSession_t ps, pCmd_t pcmd)
{
    //客户端是下载，服务器是发送
    if (0 == upload(ps->_sess_fd, pcmd->_cmd[1])) {
        sprintf(ps->_sess_buf, "file [%s] download succeed!", pcmd->_cmd[1]);
    }
    else {
        sprintf(ps->_sess_buf, "file [%s] download failed!", pcmd->_cmd[1]);
    }
    int data_len = strlen(ps->_sess_buf);
    send(ps->_sess_fd, &data_len, sizeof(int), 0);
    send(ps->_sess_fd, ps->_sess_buf, data_len, 0);
    return 0;
}
