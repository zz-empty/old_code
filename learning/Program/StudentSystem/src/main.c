#include "../include/head.h"
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    //有一个命令行参数，配置文件（账户文件名，学生信息文件名）
    if (2 != argc) {
        fprintf(stderr, "Argc error!\n");
        return -1;
    }

    const char *conf = argv[1];
    int ret;


    //初始化
    //加载账户和学生信息,用链表存储（便于增删查改）
    pUsr_t pUsrList = NULL;
    pStu_t pStuList = NULL;

    ret = init_datas(conf, &pUsrList, &pStuList);
    if (-1 == ret) {
        fprintf(stderr, "init failed!\n");
        return -1;
    }

    //登录
    //显示登录界面，并读取用户名和密码，有三次机会
    //输入密码时，用*号显示, 暂时做不到
    //登录成功后，返回用户权限, 0代表普通权限，1代表管理员权限，-1表示登录失败
    int mode = login(pUsrList);
    if (-1 == mode) {
        fprintf(stderr, "login failed!\n");
        return -1;
    } 
    
    //选择
    //进入主界面，选择具体功能
    menu(&pUsrList, &pStuList, mode);

#if 1
    //更新
    //将修改后的信息重新写入文件
    update_allInfo(conf, pUsrList, pStuList);
    return 0;
#endif
}

