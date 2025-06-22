#include "head.h"
#include "func.h"
#include "task_queue.h"

//线程清理函数
void clean_func(void *p)
{
    pTaskQueue_t pQue = (pTaskQueue_t)p;
    pthread_mutex_unlock(&pQue->_mutex);
}

//子线程的具体工作，回应客户端发来的命令
void *child_handle(void *p)
{
    //参数是任务队列(共享资源)，从里面取任务，操控锁和条件变量
    pTaskQueue_t pQue = (pTaskQueue_t)p;

    Truck_t truck;      //传输数据
    pTaskNode_t pCur = NULL;    //定义一个任务节点，用来接收任务
    Cmd_t cmd;                  //定义一个命令类型，用来接命令
    socket_t fd_client; //服务对象
    int flag = 0;       //标志位
    int ret = -1;

    while (1) {
        //从任务队列中取一个任务
        pthread_mutex_lock(&pQue->_mutex);
        pthread_cleanup_push(clean_func, pQue);//线程清理
        if (0 == pQue->_size) {
            pthread_cond_wait(&pQue->_cond, &pQue->_mutex);//等待任务
        }
        //如果退出标志为1，退出线程
        if (1 == pQue->_flag) {
            printf("thread exit!\n");
            pthread_exit(NULL);
        }
        get_TaskNode(pQue, &pCur);//得到任务
        pthread_mutex_unlock(&pQue->_mutex);

        //处理任务
        fd_client = pCur->_clifd;

        //打开日志文件
        int fd_log = open("../log/NetDisk.log", O_RDWR | O_CREAT | O_APPEND, 0666);
        record_client_msg(fd_log, fd_client, "INFO", "client connect");//记录日志

        //登录验证, 接收用户名和密码
        if (-1 == login_varify(fd_client, &truck)) {
            //登录失败，客户端输入的用户名或密码有误，退出此次任务
            flag = -1;
            send(fd_client, &flag, sizeof(int), 0);
            record_client_msg(fd_log, fd_client, "ERROR", "client login failed");//记录日志
            break;
        }

        //登录成功，继续干活
        flag = 0;
        send(fd_client, &flag, sizeof(int), 0);
        record_client_msg(fd_log, fd_client, "INFO", "client login success");//记录日志

        //接收客户端发的命令
        while (1) {
            memset(&truck, 0, sizeof(truck));
            memset(&cmd, 0, sizeof(Cmd_t));

            //先接收数据长度
            ret = recv(fd_client, &truck._data_len, sizeof(int), 0);
            if (0 == ret || 0 == truck._data_len) {
                //对端已断开
                close(fd_client);
                printf("client exit!\n");
                record_client_msg(fd_log, fd_client, "INFO", "client exit");//记录日志
                break;//此次任务结束，退出循环
            }

            //读取命令
            recv(fd_client, truck._data, truck._data_len, 0);
            memcpy(&cmd, truck._data, sizeof(Cmd_t));
            print_cmd(&cmd);
            record_client_cmd(fd_log, fd_client, "INFO", &cmd);//记录日志

            //判断是什么命令
            if (!strcmp("cd", cmd._cmd[0])) {
                do_cd(fd_client, &truck, &cmd);
            }
            else if (!strcmp("pwd", cmd._cmd[0])) {
                do_pwd(fd_client, &truck);
            }
            else if (!strcmp("ls", cmd._cmd[0])) {
                do_ls(fd_client, &truck);
            }
            else if (!strcmp("rm", cmd._cmd[0])) {
                do_rm(fd_client, &truck, &cmd);
            }
            else if (!strcmp("mkdir", cmd._cmd[0])) {
                do_mkdir(fd_client, &truck, &cmd);
            }
            else if (!strncmp("puts", cmd._cmd[0], 4)) {
                //设置客户端意外断开机制
                ret = do_puts(fd_client, &truck, &cmd);
                if (-2 == ret) {
                    //对端异常断开，无法再接收命令，退出while
                    close(fd_client);
                    printf("client erupt!\n");
                    record_client_msg(fd_log, fd_client, "ERROR", "client erupt");//记录日志
                    break;
                }
            }
            else if (!strncmp("gets", cmd._cmd[0], 4)) {
                //设置客户端意外断开机制
                if (-2 == do_gets(fd_client, &truck, &cmd)) {
                    //对端意外断开，无法再接收命令，退出while
                    close(fd_client);
                    printf("client erupt!\n");
                    record_client_msg(fd_log, fd_client, "ERROR", "client erupt");//记录日志
                    break;
                }
            }
            else {
                //非法命令
                record_client_msg(fd_log, fd_client, "ERROR", "Invalid command");//记录日志

                //回应客户端
                strncpy(truck._data, "Invalid command!", BUF_SIZE);
                truck._data_len = sizeof(truck._data);
                send(fd_client, &truck, sizeof(int) + truck._data_len, 0);
            }
        }//end of while(1) 接收客户端命令

        //本次连接已结束，释放任务节点
        free(pCur);
        pCur = NULL;

        pthread_cleanup_pop(1);//线程清理
    }//end of while(1) 线程 
}
