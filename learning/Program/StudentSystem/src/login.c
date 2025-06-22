#include "../include/head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pUsr_t find_form_usrlist(pUsr_t pUsrList, pUsr_t tmp);

//返回用户权限, -1表示登录失败
int login(pUsr_t pUsrList)
{
    pUsr_t ret = NULL;

    //三次机会
    for (int i = 0; i < 3; ++i) {
        //待验证用户名，密码
        Usr_t tmp;
        memset(tmp._name, 0, sizeof(tmp._name));
        memset(tmp._pwd, 0, sizeof(tmp._pwd));
        tmp._mode = 0;

        system("clear");
        puts("--------------------Login in-------------------");
        printf("please input usrname: ");
        fscanf(stdin, "%s", tmp._name);
        printf("please input usrcode: ");
        //星号显示密码, 暂时做不到
        fscanf(stdin, "%s", tmp._pwd);

        //在用户链表中查找
        ret = find_form_usrlist(pUsrList, &tmp);    
        if (NULL == ret) {
            if (2 == i) {
                //三次都输入错误
                return -1;
            }
            system("clear");
            printf("please input again, incorrect username or password!\n");
            continue;
        }
        else {
            break;
        }
    }
    return ret == NULL ? -1 : ret->_mode;
}

pUsr_t find_form_usrlist(pUsr_t pUsrList, pUsr_t pTmp)
{
    //遍历链表，对比用户名和密码
    for (pUsr_t pCur = pUsrList; pCur; pCur = pCur->pNext) {
        if (!strcmp(pCur->_name, pTmp->_name) && !strcmp(pCur->_pwd, pTmp->_pwd)) {
            return pCur;
        }
    } 
    return NULL;
}
