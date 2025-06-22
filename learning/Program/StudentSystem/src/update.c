#include "../include/head.h"
#include <stdio.h>

int update_allInfo(const char *conf, pUsr_t pUsrList, pStu_t pStuList)
{
    //以w模式打开用户文件和学生信息文件
    //将用户链表和学生链表重新写入
    
    //从配置文件中，拿到用户文件和学生信息文件
    FILE *fconfig = (FILE*)fopen(conf, "r");
    RET_CHECK(fconfig, NULL, "open conf error!");

    //为防止溢出，路径长度设大点
    char usrfile[30] = {0};
    char usrpath[128] = {0};
    char stufile[30] = {0};
    char stupath[128] = {0};
    fscanf(fconfig, "%s", usrfile);
    fscanf(fconfig, "%s", stufile);
    sprintf(usrpath, "../conf/%s", usrfile);
    sprintf(stupath, "../conf/%s", stufile);

    fclose(fconfig);

    //将用户链表写入用户文件
    FILE *fusr = (FILE*)fopen(usrpath, "w");
    RET_CHECK(fusr, NULL, "open fusr error!");

    for (pUsr_t pCur = pUsrList; pCur; pCur = pCur->pNext) {
        fprintf(fusr, "%s\t%s\t%d\n", pCur->_name, pCur->_pwd, pCur->_mode);
    }

    fclose(fusr);

    //将学生链表，写入学生信息文件
    FILE *fstu = (FILE*)fopen(stupath, "w");
    RET_CHECK(fstu, NULL, "open fstu error!");

    for (pStu_t pCur = pStuList; pCur; pCur = pCur->pNext) {
        fprintf(fstu, "%d\t%s\t%c\t%5.2f\t%5.2f\t%5.2f\n", pCur->_id, pCur->_name, pCur->_gender, 
                pCur->_score1, pCur->_score2, pCur->_score3);
    }

    fclose(fstu);
    return 0;
}
