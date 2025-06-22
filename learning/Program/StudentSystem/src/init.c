#include "../include/head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void init_usrlist(FILE *fusr, pUsr_t* ppUsrList);
void init_stulist(FILE *fstu, pStu_t* ppStuList);
void headInsertUsr(pUsr_t* ppUsrList, pUsr_t pTmp);
void sortInsertStu(pStu_t *ppStuList, pStu_t pTmp);
void displayUsr(pUsr_t pUsrList);
void displayStu(pStu_t ppStuList);

void sort_stulist(pStu_t *ppStuList);

int init_datas(const char *conf, pUsr_t *ppUsrList, pStu_t *ppStuList)
{
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

    //从用户文件中读取，初始化用户链表
    FILE *fusr = (FILE*)fopen(usrpath, "r+");
    RET_CHECK(fusr, NULL, "open fusr error!");
    init_usrlist(fusr, ppUsrList);
    fclose(fusr);

    /* displayUsr(*ppUsrList); */

    //从学生信息文件中读取，初始化学生链表
    FILE *fstu = (FILE*)fopen(stupath, "rb+");
    RET_CHECK(fstu, NULL, "open fstu error!");
    init_stulist(fstu, ppStuList);
    fclose(fstu);

    /* displayStu(*ppStuList); */

    return 0;
}

void init_usrlist(FILE *fusr, pUsr_t* ppUsrList)
{
    while (1) {
        Usr_t tmp;
        int ret = fscanf(fusr, "%s%s%d", tmp._name, tmp._pwd, &tmp._mode);
        if (EOF == ret) {
            break;
        }
        headInsertUsr(ppUsrList, &tmp);
    }

}

void headInsertUsr(pUsr_t *ppUsrList, pUsr_t pTmp)
{
    pUsr_t pNew = (pUsr_t)calloc(1, sizeof(Usr_t));
    memcpy(pNew, pTmp, sizeof(Usr_t));
    pNew->pNext = NULL;

    if (NULL == *ppUsrList) {
        //链表为空时
        *ppUsrList = pNew;
    }
    else {
        pNew->pNext = *ppUsrList;
        *ppUsrList = pNew;
    }
}

void init_stulist(FILE *fstu, pStu_t* ppStuList)
{
    while (1) {
        Stu_t tmp;
        int ret = fscanf(fstu, "%d%s %c%f%f%f", &tmp._id, tmp._name, &tmp._gender, &tmp._score1, &tmp._score2, &tmp._score3);
        if (EOF == ret) {
            return;
        }
        displayStu(*ppStuList);

        sortInsertStu(ppStuList, &tmp);
    }
}

void sortInsertStu(pStu_t *ppStuList, pStu_t pTmp)
{

    pStu_t pNew = (pStu_t)calloc(1, sizeof(Stu_t));
    memcpy(pNew, pTmp, sizeof(Stu_t));
    pNew->pNext = NULL;

#if 0
    if (NULL == *ppStuList) {
        //链表为空时
        *ppStuList = pNew;
    }
    else {
        pStu_t pPre = *ppStuList;
        pStu_t pCur = pPre->pNext;

        for (; pCur; pPre = pCur, pCur = pCur->pNext) {
        }

        pPre->pNext = pNew;
    }

#else
    if (NULL == *ppStuList) {
        //链表为空时
        *ppStuList = pNew;
    }
    else if (pNew->_id < (*ppStuList)->_id) {
        pNew->pNext = *ppStuList;
        *ppStuList = pNew;
    }
    else {
        pStu_t pPre = *ppStuList;
        pStu_t pCur = pPre->pNext;

        for (; pCur; pPre = pCur, pCur = pCur->pNext) {
            if (pNew->_id < pCur->_id) {
                pPre->pNext = pNew;
                pNew->pNext = pCur;
                return;
            }
        }

        //新节点id最大
        if (NULL == pCur) {
            pPre->pNext = pNew;
        }
    }
#endif
}


void displayUsr(pUsr_t pUsrList)
{
    for (; pUsrList; pUsrList = pUsrList->pNext) {
        printf("usrname: %s, usrpwd = %s\n", pUsrList->_name, pUsrList->_pwd);
    }
}

void displayStu(pStu_t pStuList)
{
    for (; pStuList; pStuList = pStuList->pNext) {
        printf("id:%d\tname:%s\tgender:%s\ts1:%5.2f\ts2:%5.2f\ts3:%5.2f\n", 
               pStuList->_id,
               pStuList->_name,
               pStuList->_gender == '0' ? "女" : "男",
               pStuList->_score1,
               pStuList->_score2,
               pStuList->_score3);
    }
}
