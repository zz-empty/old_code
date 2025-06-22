#include "../include/head.h"
#include "../include/thread_pool.h"
#include "../include/work_que.h"
#include "../include/func.h"
#include "../include/mysql_func.h"

int cd(int clientFd, train_t th_train, pActive_user_node_t pNode);
int ls(int clientFd, train_t th_train, pActive_user_node_t pNode);
int pwd(int clientFd, train_t th_train, pActive_user_node_t pNode);
int rm(int clientFd, train_t th_train, pActive_user_node_t pNode);
int mymkdir(int clientFd, train_t th_train, pActive_user_node_t pNode);
int download(int clientFd, train_t th_train, active_user_node_t uNode);
int upload(int clientFd, train_t th_train, active_user_node_t uNode);

void clean_func(void *p){
    pQue_t pque = (pQue_t)p;
    pthread_mutex_unlock(&pque->mutex);
}
//线程池初始化
int thread_pool_init(pThread_pool pPoll,int thread_num)
{
    que_init(&pPoll->que);
    pPoll->pthread_num = thread_num;
    pPoll->pthid = (pthread_t *)calloc(thread_num,sizeof(pthread_t));
    pPoll->download_thread = thread_func;
    pPoll->start_flag = 0;
    return 0;
}
//线程函数
void * thread_func(void *p){
    pQue_t pque= (pQue_t)p;//操作同一把锁
    pNode_t pcur;//用来保存拿到任务的指针
    int gettag = 1;
    while(1){
        pthread_mutex_lock(&pque->mutex);//加锁
        pthread_cleanup_push(clean_func,pque);//使用线程清理函数清理互斥锁资源，避免因线程意外关闭而造成锁资源无法释放,通常放在所要清理的资源后
        if(!pque->que_size){//如果队列为空
            pthread_cond_wait(&pque->cond,&pque->mutex);//就睡觉，睡在mutex上
        }
        gettag = que_get(pque,&pcur);//从队列中获取任务
        pthread_mutex_unlock(&pque->mutex);//解锁
        if(!gettag){//如果clientFd为-1，说明main线程发来信号，关闭
            if(-1 == pcur->new_fd){
                free(pcur);
                pcur = NULL;
                pthread_exit(NULL);
            }
            //日志
            char str[256] = {0};
            int log_fd = open("log",O_CREAT|O_RDWR|O_APPEND,0666);
            time_t now;
            //否则执行任务
            train_t train;
            msg_t the_msg;
            command_t the_command;
            int epfd = 0;
            epfd = epoll_create(1);
            struct epoll_event evs[2];
            epoll_add(epfd,pcur->new_fd);
            int epoll_ready_num = 0;
            int i = 0;
            int ret = 0;
            active_user_node_t node;
            memset(&node, 0, sizeof(node));
            while(1){
                epoll_ready_num = epoll_wait(epfd,evs,2,-1);
                for(i = 0; i < epoll_ready_num; ++i){
                    if(evs[i].data.fd == pcur->new_fd){
                        memset(&train,0,sizeof(train));
                        memset(&the_msg,0,sizeof(the_msg));
                        memset(&the_command,0,sizeof(the_command));
                        ret = recv(pcur->new_fd,&train.data_len,4,0);
                        printf("len = %d\n",train.data_len);
                        if(0 == ret){
                            printf("客户端退出\n");
                            close(pcur->new_fd);
                            break;
                        }
                        printf("%d\n",train.data_len);
                        recv(pcur->new_fd,&train.buf,1028,0);
                        /* recv(pcur->new_fd,&train.buf,train.data_len,0); */
                        printf("buf = %s\n",train.buf);
                        memcpy(&the_msg,train.buf,sizeof(the_msg));
                        memcpy(&the_command,the_msg.buf,sizeof(the_command));
                        printf("msg type %c\n", the_msg.msg_type);
                        printf("cmd is %s\n",the_command.command_content[0]);

                        if('r' == the_msg.msg_type){//msg_type标志位为r,表明是注册信息，进入注册函数处理程序
                            printf("client want registration\n");
                            user_registration(pcur->new_fd,train);
                            printf("finish registration\n");
                            time(&now);
                            sprintf(str,"%s%s%s%s","some client finish registration ","time: ",ctime(&now),"\n");
                            write(log_fd,str,strlen(str));
                            memset(str,0,sizeof(str));
                        }
                        else if('i' == the_msg.msg_type){
                            printf("client want login\n");
                            user_login(pcur->new_fd,train, &node);
                            printf("cur path %d\n", node.cur_path_id);
                            printf("finish login\n");
                            time(&now);
                            sprintf(str,"%s%d%s%s%s%s","client ",node.user_id," finish login ","time: ",ctime(&now),"\n");
                            write(log_fd,str,strlen(str));
                            memset(str,0,sizeof(str));
                        }
                        else if(the_msg.msg_type == 's'){
                            //短命令
                            if(!strcmp(the_command.command_content[0], "cd")){
                                printf("cd\n");
                                cd(pcur->new_fd, train, &node);
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));

                            }
                            else if(!strcmp(the_command.command_content[0], "ls")){
                                printf("ls\n");
                                ls(pcur->new_fd, train, &node);                                
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));
                            }
                            else if(!strcmp(the_command.command_content[0], "pwd")){
                                printf("pwd\n");
                                pwd(pcur->new_fd, train, &node);                                
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));
                            }
                            else if(!strcmp(the_command.command_content[0], "rm")){
                                printf("rm\n");
                                rm(pcur->new_fd, train, &node);                                
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));
                            }
                            else if(!strcmp(the_command.command_content[0], "mkdir")){
                                printf("mkdir\n");
                                mymkdir(pcur->new_fd, train, &node);                                
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));
                            }
                        }
                        else if(the_msg.msg_type == 'l'){
                            //长命令
                            if(!strcmp(the_command.command_content[0],"download")){
                                //请求下载文件
                                /* strcpy(sql,"insert into userinfo (username, salt, cryptpasswd) values ("); */
                                /* sprintf(sql, "%s'%s','%s','%s')", query,userinfo.username,userinfo.salt,userinfo.cryptpasswd); */
                                printf("before trans\n");

                                download(pcur->new_fd, train, node);

                                printf("after trans\n");
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));

                            }
                            if(!strcmp(the_command.command_content[0],"upload")){
                                //请求上传
                                printf("before up\n");
                                upload(pcur->new_fd, train, node);
                                printf("after up\n");
                                time(&now);
                                sprintf(str,"%s%d%s%s%s%s%s","client ",node.user_id," ",the_command.command_content[0]," time: ",ctime(&now),"\n");
                                write(log_fd,str,strlen(str));
                                memset(str,0,sizeof(str));
                            }

                        }//end if msg.type == 'l'

                    }
                }//end for
            }//end while(1)
            free(pcur);
            pcur = NULL;
        }
        pthread_cleanup_pop(1);
    }
    pthread_exit(NULL);
}
//线程启动函数
int thread_pool_start(pThread_pool p){
    int i = 0;
    if(0 == p->start_flag){
        for(i = 0; i< p->pthread_num; ++i){
            pthread_create(p->pthid+i,NULL,p->download_thread,&p->que);
            p->start_flag = 1;
        }
    }
    return 0;
}








int cd(int clientFd, train_t th_train, pActive_user_node_t pNode){
    msg_t cd_msg;
    command_t cd_cmd;
    memcpy(&cd_msg, th_train.buf, sizeof(cd_msg));
    memcpy(&cd_cmd, cd_msg.buf, sizeof(cd_cmd));
    char query[300] = {0};
    char *result = (char *)calloc(128,1);

    //三种选择：家目录、上级目录、下级目录，修改当前路径
    if(!strcmp(cd_cmd.command_content[1], "~")){
        strcpy(query,"select id from virtual_file where owner_id =");
        sprintf(query, "%s%d%s", query, pNode->user_id, " and parent_id = 1");
        mysql_query1(query,&result);
        printf("result is %s\n",result);
        //修改当前路径id
        pNode->cur_path_id = atoi(result);
        //修改当前路径
        printf("path %s\n",pNode->cur_path);
        int i = 0;
        while(pNode->cur_path[i] != '/'){
            //printf("i = %c\n",pNode->cur_path[i]);
            ++i;
        }
        pNode->cur_path[i] = '\0';
        printf("path %s\n",pNode->cur_path);
        strcpy(cd_msg.buf, pNode->cur_path);
        printf("path %s\n",pNode->cur_path);
    }
    else if(!strcmp(cd_cmd.command_content[1], "..")){
        strcpy(query,"select parent_id from virtual_file where id =");
        sprintf(query, "%s%d%s", query, pNode->cur_path_id, "");
        mysql_query1(query,&result);
        printf("result is %s\n",result);
        //修改当前路径id
        pNode->cur_path_id = atoi(result);
        int i = strlen(pNode->cur_path);
        //回到上一级
        while(pNode->cur_path[i] != '/'){
            --i;
        }
        pNode->cur_path[i] = '\0';
        strcpy(cd_msg.buf, pNode->cur_path);
    }
    else{
        //selec id form virtual_file where uNode.cur_path_id = parent_id;
        strcpy(query,"select id from virtual_file where parent_id =");
        sprintf(query, "%s%d%s%s%s", query, pNode->cur_path_id, " and filename = '", cd_cmd.command_content[1], "'");
        mysql_query1(query,&result);
        printf("result is %s\n",result);
        //修改当前路径id
        pNode->cur_path_id = atoi(result);
        //进入下一级
        strcat(pNode->cur_path, "/");
        strcat(pNode->cur_path, cd_cmd.command_content[1]);
        strcpy(cd_msg.buf, pNode->cur_path);
    }
    cd_msg.msg_from = 's';
    cd_msg.msg_type = 'm';
    memcpy(th_train.buf, &cd_msg, sizeof(cd_msg));
    send(clientFd, &th_train, sizeof(th_train), 0);
    return 0;
}

int ls(int clientFd, train_t th_train, pActive_user_node_t pNode){
    msg_t ls_msg;
    command_t ls_cmd;
    memcpy(&ls_msg, th_train.buf, sizeof(ls_msg));
    memcpy(&ls_cmd, ls_msg.buf, sizeof(ls_cmd));
    char query[300] = {0};
    char *result = (char *)calloc(128,1);
printf("cur path = %d\n",pNode->cur_path_id);
    strcpy(query,"select filename from virtual_file where parent_id =");
    sprintf(query, "%s%d%s", query, pNode->cur_path_id, "");
    mysql_query1(query,&result);
    printf("result is %s\n",result);
    strcpy(ls_msg.buf, result);
    ls_msg.msg_from = 's';
    ls_msg.msg_type = 'm';
    memcpy(th_train.buf, &ls_msg, sizeof(ls_msg));
    send(clientFd, &th_train, sizeof(th_train), 0);
    return 0;
}

int pwd(int clientFd, train_t th_train, pActive_user_node_t pNode){
    msg_t pwd_msg;
    command_t pwd_cmd;
    memcpy(&pwd_msg, th_train.buf, sizeof(pwd_msg));
    memcpy(&pwd_cmd, pwd_msg.buf, sizeof(pwd_cmd));
    strcpy(pwd_msg.buf, pNode->cur_path);
    pwd_msg.msg_from = 's';
    pwd_msg.msg_type = 'm';
    memcpy(th_train.buf, &pwd_msg, sizeof(pwd_msg));
    send(clientFd, &th_train, sizeof(th_train), 0);
    return 0;
}

int rm(int clientFd, train_t th_train, pActive_user_node_t pNode){
    msg_t rm_msg;
    command_t rm_cmd;
    memcpy(&rm_msg, th_train.buf, sizeof(rm_msg));
    memcpy(&rm_cmd, rm_msg.buf, sizeof(rm_cmd));
    char query[300] = {0};
    char *result = (char *)calloc(128,1);

    strcpy(query,"select id from virtual_file where filename ='");
    sprintf(query, "%s%s%s%d", query, rm_cmd.command_content[1], "' and parent_id = ", pNode->cur_path_id);
    puts(query);
    mysql_query1(query,&result);
    printf("result is %s\n",result);
    sprintf(query, "%s%d", "delete from virtual_file where id = ", atoi(result));
    puts(query);
    mysql_delete(query);
    rm_msg.msg_from = 's';
    rm_msg.msg_type = 'm';
    strcpy(rm_msg.buf, "success");
    memcpy(th_train.buf, &rm_msg, sizeof(rm_msg));
    send(clientFd, &th_train, sizeof(th_train), 0);
    return 0;
}

int mymkdir(int clientFd, train_t th_train, pActive_user_node_t pNode){
    msg_t mk_msg;
    command_t mk_cmd;
    memcpy(&mk_msg, th_train.buf, sizeof(mk_msg));
    memcpy(&mk_cmd, mk_msg.buf, sizeof(mk_cmd));
    char query[300] = {0};
    char *result = (char *)calloc(128,1);

    strcpy(query,"insert into virtual_file (filename, parent_id, owner_id, type, filesize, md5) values ('");
    sprintf(query, "%s%s', %d, %d, 'd', 0, 0)", query, mk_cmd.command_content[1], pNode->cur_path_id, pNode->user_id);
    mysql_insert(query);
    mk_msg.msg_from = 's';
    mk_msg.msg_type = 'm';
    strcpy(mk_msg.buf, "success");
    memcpy(th_train.buf, &mk_msg, sizeof(mk_msg));
    send(clientFd, &th_train, sizeof(th_train), 0);
    return 0;
}


int download(int clientFd, train_t th_train, active_user_node_t uNode){
    //判断文件是否存在
    msg_t d_msg;
    command_t d_cmd;
    memcpy(&d_msg, th_train.buf, sizeof(d_msg));
    memcpy(&d_cmd, d_msg.buf, sizeof(d_cmd));


    char query[300] = {0};
    char *result = (char *)calloc(128,1);

    strcpy(query,"select md5 from virtual_file where filename ='");
    sprintf(query, "%s%s%s%d", query, d_cmd.command_content[1], "' and parent_id =", uNode.cur_path_id);
    mysql_query1(query,&result);
    printf("result is %s\n",result);
    //存在
    if(strcmp(result,"noexist")){
        //
        long len = atoi(d_cmd.command_content[2]);

        int d_fd = open(result, O_RDWR);
        lseek(d_fd, len, SEEK_SET);
        struct stat fileInfo;
        bzero(&fileInfo, sizeof(fileInfo));
        //获取文件长度
        fstat(d_fd, &fileInfo);
        d_msg.msg_from = 's';
        d_msg.msg_type = 'f';
        th_train.data_len = fileInfo.st_size;
        memcpy(th_train.buf, &d_msg, sizeof(d_msg));
        send(clientFd, &th_train, sizeof(th_train), 0);
        //零拷贝3. splice
        //ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags);
        int sfd[2];
        pipe(sfd);

        printf("before splice\n");


        int sendLen = 0;
        while(sendLen < fileInfo.st_size){
            //splice可以限制传输速率
            int ret = splice(d_fd, 0, sfd[1], 0, 128, 0);
            ret = splice(sfd[0], 0, clientFd, 0, ret, 0);
            sendLen += ret;
        }

        return 0;
    }
    //不存在
    else{
        d_msg.msg_from = 's';
        d_msg.msg_type = 'm';
        strcpy(d_msg.buf, "no such file!");
        memcpy(th_train.buf, &d_msg, sizeof(d_msg));
        send(clientFd, &th_train, sizeof(th_train), 0);
        return 0;
    }
}
int upload(int clientFd, train_t th_train, active_user_node_t uNode){
    msg_t u_msg;
    command_t u_cmd;
    int filesize = th_train.data_len;
    memcpy(&u_msg, th_train.buf, sizeof(u_msg));
    memcpy(&u_cmd, u_msg.buf, sizeof(u_cmd));

    char query[300] = {0};
    char *result = (char *)calloc(128,1);

    strcpy(query,"select md5 from virtual_file where md5 ='");
    sprintf(query, "%s%s%s", query, u_cmd.command_content[2], "'");
    mysql_query1(query,&result);
    printf("result is %s\n",result);

    //判断文件是否已有
    //没有
    if(!strcmp(result, "noexist")){
        int u_fd = open(u_cmd.command_content[2], O_RDWR|O_CREAT, 0666);
        u_msg.msg_from = 's';
        u_msg.msg_type = 't';
        memset(u_msg.buf, 0, sizeof(u_msg.buf));
        memcpy(th_train.buf, &u_msg, sizeof(u_msg));
        send(clientFd, &th_train, sizeof(th_train), 0);
        //零拷贝3. splice
        //ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags);
        int sfd[2];
        pipe(sfd);

        printf("before splice\n");

        int sendLen = 0;
        while(sendLen < filesize){
            //splice可以限制传输速率
            int ret = splice(clientFd, 0, sfd[1], 0, 128, 0);
            ret = splice(sfd[0], 0, u_fd, 0, ret, 0);
            sendLen += ret;

        }

    }
    //已有，秒传
    else{
        u_msg.msg_from = 's';
        u_msg.msg_type = 'u';
        memset(u_msg.buf, 0, sizeof(u_msg.buf));
        memcpy(th_train.buf, &u_msg, sizeof(u_msg));
        send(clientFd, &th_train, sizeof(th_train), 0);
    }
    //更新虚拟文件表
    sprintf(query, "%s%s',%d,%d,'f',%d,'%s')", "insert into virtual_file (filename,parent_id,owner_id,type,filesize,md5) values('",
            u_cmd.command_content[1], uNode.cur_path_id, uNode.user_id, th_train.data_len, u_cmd.command_content[2]);
    puts(query);
    mysql_insert(query);
    return 0;
}                 
