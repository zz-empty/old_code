#include "head.h"
#include "func.h"
#include "thread_pool.h"
#include "task_queue.h"

//线程清理函数
void clean_func(void *p)
{
    pTaskQueue_t pQue = (pTaskQueue_t)p;
    pthread_mutex_unlock(&pQue->_mutex);
}

//子线程, 处理每一个客户端的任务，和主进程退出
//客户端的登录或注册, 以及客户端的普通命令
void *child_handle(void *p)
{
    pTaskQueue_t pQue = (pTaskQueue_t)p;    //参数是任务队列(共享资源)，从里面取任务，操控锁和条件变量

    pTaskNode_t pCur = NULL;    //定义一个任务节点，用来获取任务
    socket_t fd_client;         //客户端套接字
    Truck_t truck;              //传输缓冲区
    Msg_t msg;                  //消息
    Cmd_t cmd;                  //命令
    int ret = -1;

    //处理每一个新的客户端连接
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
        printf("---task start---\n");

        //记录当前用户信息
        Active_user_node_t node;
        memset(&node, 0, sizeof(Active_user_node_t));

        //打开日志文件
        int fd_log = open("../log/NetDisk.log", O_RDWR | O_CREAT | O_APPEND, 0666);
        record_client_msg(fd_log, fd_client, "INFO", "client connect");//记录日志


        //接收一个客户端消息，判断要干什么
        while (1) {
            memset(&truck, 0, sizeof(truck));
            memset(&msg, 0, sizeof(Msg_t));
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

            //卸货，得到信息
            recv(fd_client, truck._data, truck._data_len, 0);
            memcpy(&msg, truck._data, sizeof(Msg_t));

            if ('i' == msg._type) {         //登录信息
                if (-1 == user_login(fd_client, &truck, &node)) {
                    //登录失败，客户端输入的用户名或密码有误
                    record_client_msg(fd_log, fd_client, "ERROR", "client login failed");//记录日志
                }
                else {
                    //登录成功，继续干活
                    record_client_msg(fd_log, fd_client, "INFO", "client login success");//记录日志
                }
            }
            else if ('r' == msg._type) {    //注册信息
                if (-1 == user_register(fd_client, &truck)) {
                    //注册失败，用户已存在
                    record_client_msg(fd_log, fd_client, "ERROR", "client register failed");//记录日志
                }
                else {
                    //注册成功
                    record_client_msg(fd_log, fd_client, "INFO", "client register success");//记录日志
                }
            }
            else if ('c' == msg._type) {    //命令信息
                //接收命令
                memcpy(&cmd, msg._buf, sizeof(Cmd_t));
                print_cmd(&cmd);
                record_client_cmd(fd_log, fd_client, "INFO", &cmd);//记录日志

                //判断是什么命令
                if (!strcmp("cd", cmd._cmd[0])) {
                    do_cd(fd_client, &truck);
                }
                else if (!strcmp("pwd", cmd._cmd[0])) {
                    do_pwd(fd_client, &truck);
                }
                else if (!strcmp("ls", cmd._cmd[0])) {
                    do_ls(fd_client, &truck);
                }
                else if (!strcmp("rm", cmd._cmd[0])) {
                    do_rm(fd_client, &truck);
                }
                else if (!strcmp("mkdir", cmd._cmd[0])) {
                    do_mkdir(fd_client, &truck);
                }
                else if (!strncmp("puts", cmd._cmd[0], 4)) {
                    //设置客户端意外断开机制
                    ret = do_puts(fd_client, &truck);
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
                    if (-2 == do_gets(fd_client, &truck)) {
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
            }
        }//end of while(1) 接收客户端命令

        //本次连接已结束，释放任务节点
        free(pCur);
        pCur = NULL;
        printf("---task finish---\n");

        pthread_cleanup_pop(1);//线程清理
    }//end of while(1) 线程 
}

//初始化线程池
int init_ThreadPool(pThreadPool_t pPool, int thread_num)
{
    pPool->_thread_num = thread_num;
    pPool->_pthid = (pthread_t*)calloc(thread_num, sizeof(pthread_t));
    init_TaskQueue(&pPool->_que);
    return 0;
}

//启动线程池
int boot_ThreadPool(pThreadPool_t pPool)
{
    for (int i = 0; i < pPool->_thread_num; ++i) {
        pthread_create(pPool->_pthid + i, NULL, child_handle, &pPool->_que);
    }
    return 0;
}

//关闭线程池
int close_ThreadPool(pThreadPool_t pPool) 
{
    for (int i = 0; i < pPool->_thread_num; ++i) {
        pthread_join(pPool->_pthid[i], NULL);
    }
    return 0;
}

//销毁线程池资源
int destory_ThreadPool(pThreadPool_t pPool)
{
    free(pPool->_pthid);
    return 0;
}
