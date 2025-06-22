#include "../include/head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void menu_title();//界面头
void menu_0();//普通权限的菜单
void menu_1();//管理员权限的菜单
void stu_title();//学生信息头
void usr_title();//账户信息头
void my_pause();//按任意键继续

void show_stuInfo(pStu_t pCur);
void show_usrInfo(pUsr_t p);
int sort_insert_stu(pStu_t* ppStuList, pStu_t tmp);
int sort_insert_usr(pUsr_t* ppUsrList, pUsr_t tmp);

int func_findStu(pStu_t pStuList);
int func_addStu(pStu_t* ppStuList);
int func_updateStu(pStu_t pStuList);
int func_eraseStu(pStu_t* ppStuList);
void show_all_stu(pStu_t pStuList);

int func_findUsr(pUsr_t pUsrList);
int func_addUsr(pUsr_t* ppUsrList);
int func_updateUsr(pUsr_t pUsrList);
int func_eraseUsr(pUsr_t* ppUsrList);
void show_all_usr(pUsr_t pUsrList);


//根据用户权限，显示菜单界面
//账户的增删查改, 学生信息的增删查改
void menu(pUsr_t* ppUsrList, pStu_t* ppStuList, int mode)
{

    if (0 == mode) {
        //普通权限只能查找学生信息
        while (1) {
            //清空原有界面，显示新界面
            system("clear");
            menu_title();
            menu_0();
            //录入选择
            printf("select a number:");
            int option = -1;
            scanf("%d", &option);
            //0---退出  1---查找
            if (0 == option) {
                break;
            }
            else if (1 == option){
                func_findStu(*ppStuList);
                my_pause();
            }
            else if (2 == option) {
                system("clear");
                show_all_stu(*ppStuList);
                my_pause();
            }
            else {
                printf("选择无效，请重新选择！\n");
                my_pause();
                continue;
            }
        }
    }
    else if (1 == mode) {
        //管理员权限拥有全部功能
        while (1) {
            //清空原有界面，显示新界面
            system("clear");
            menu_title();
            menu_1();
            //录入选择
            printf("select a number:");
            int option = -1;
            scanf("%d", &option);
            //0---退出  1---查找
            //1-5  学生的查、增、删、改、显示全部
            //6-10 账户的查、增、删、改、显示全部
            if (0 == option) {
                break;
            }
            else if (1 == option){
                system("clear");
                func_findStu(*ppStuList);
                my_pause();
            }
            else if (2 == option) {
                system("clear");
                func_addStu(ppStuList);
                my_pause();
            }
            else if (3 == option) {
                system("clear");
                func_updateStu(*ppStuList);
                my_pause();
            }
            else if (4 == option) {
                system("clear");
                func_eraseStu(ppStuList);
                my_pause();
            }
            else if (5 == option) {
                system("clear");
                show_all_stu(*ppStuList);
                my_pause();
            }
            else if (6 == option) {
                system("clear");
                func_findUsr(*ppUsrList);
                my_pause();

            }
            else if (7 == option) {
                system("clear");
                func_addUsr(ppUsrList);
                my_pause();
            }
            else if (8 == option) {
                system("clear");
                func_updateUsr(*ppUsrList);
                my_pause();
            }
            else if (9 == option) {
                system("clear");
                func_eraseUsr(ppUsrList);
                my_pause();
            }
            else if (10 == option) {
                system("clear");
                show_all_usr(*ppUsrList);
                my_pause();
            }
            else {
                printf("选择无效，请重新选择！\n");
                my_pause();
                continue;
            }
        }
    }
}

int func_addStu(pStu_t* ppStuList)
{
    //输入一个学生的信息：id, name, gender, s1, s2, s3
    //判断id是否重复，如果重复报错返回，不重复则有序插入链表中
    Stu_t tmp;
    printf("please input new stu_id: ");
    scanf("%d", &tmp._id);

    for (pStu_t pCur = *ppStuList; pCur; pCur = pCur->pNext) {
        if (tmp._id == pCur->_id) {
            printf("this stu_id is already exist!\n");
            return -1;
        }
    }

    printf("please input new stu_name: ");
    scanf("%s", tmp._name);

    getchar();
    printf("please input new stu_gender(0-woman, 1-man): ");
    char c = 'a';
    scanf("%c", &c);
    if ('0' != c && '1' != c) {
        fprintf(stderr, "gender format error!\n");
        return -1;
    }
    tmp._gender = c;

    printf("please input new stu_score1: ");
    scanf("%f", &tmp._score1);
    printf("please input new stu_score2: ");
    scanf("%f", &tmp._score2);
    printf("please input new stu_score3: ");
    scanf("%f", &tmp._score3);

    sort_insert_stu(ppStuList, &tmp);
    printf("insert success!\n");
    return 0;
}

int sort_insert_stu(pStu_t* ppStuList, pStu_t tmp)
{
    pStu_t pNew = (pStu_t)calloc(1, sizeof(Stu_t));
    memcpy(pNew, tmp, sizeof(Stu_t));
    pNew->pNext = NULL;

    if (NULL == *ppStuList) {
        //链表为空
        *ppStuList = pNew;
    }
    else if (pNew->_id < (*ppStuList)->_id) {
        //新节点id最小
        pNew->pNext = *ppStuList;
        *ppStuList = pNew;
    }
    else if (NULL == (*ppStuList)->pNext) {
        //链表只有一个元素，且id小于新节点
        (*ppStuList)->pNext = pNew;
    }
    else {
        //链表至少有两个节点，且表头id小于新节点
        //找到一个pCur节点id大于新节点，将新节点插入pPre后
        //如果没找到，插入最后
        pStu_t pPre = *ppStuList;
        pStu_t pCur = pPre->pNext;

        for (; pCur; pPre = pCur, pCur = pCur->pNext) {
            if (pCur->_id > pNew->_id) {
                pPre->pNext = pNew;
                pNew->pNext = pCur;
                break;
            }
        }

        if (NULL == pCur) {
            pPre->pNext = pNew;
        }
    }

    return 0;
}


int func_eraseStu(pStu_t* ppStuList)
{
    //如果空，显示空退出
    //得到删除stu_id，查找若存在删除，若不存在提示退出
    //删表头时，更新表头
    if (NULL == *ppStuList) {
        fprintf(stderr, "Empty!\n");
        return -1;
    }

    int id;
    printf("please input delete stu_id: ");
    scanf("%d", &id);

    pStu_t pCur = *ppStuList;
    if (id == (*ppStuList)->_id) {
        *ppStuList = pCur->pNext;  
    }
    else {
        pStu_t pPre = pCur;
        pCur = pCur->pNext;  
        for (; pCur; pPre = pCur, pCur = pCur->pNext) {
            if (id == pCur->_id) {
                pPre->pNext = pCur->pNext;
                break;
            }
        }
    }

    if (NULL == pCur) {
        fprintf(stderr, "Not found the stu_id!\n");
        return -1;
    }
    else {
        printf("Delete success!\n");
        free(pCur);
        pCur = NULL;
        return 0;
    }
}

int func_updateStu(pStu_t pStuList)
{
    //输入待修改的stu_id, 若存在则输入修改信息
    printf("please input modify stu_id: ");
    int id;
    scanf("%d", &id);

    pStu_t pCur = NULL;
    for (pCur = pStuList; pCur; pCur = pCur->pNext) {
        if (id == pCur->_id) {
            puts("1-modify stu_name");
            puts("2-modify stu_gender");
            puts("3-modify stu_score1");
            puts("4-modify stu_score2");
            puts("5-modify stu_score3");
            puts("6-modify all");

            int option;
            scanf("%d", &option);

            switch (option) {
            case 1:
                printf("modify stu_name: ");
                scanf("%s", pCur->_name);
                break;
            case 2:
                printf("modify stu_gender(0-woman 1-man): ");
                scanf("%c", &pCur->_gender);
                break;
            case 3:
                printf("modify stu_score1: ");
                scanf("%f", &pCur->_score1);
                break;
            case 4:
                printf("modify stu_score2: ");
                scanf("%f", &pCur->_score2);
                break;
            case 5:
                printf("modify stu_score3: ");
                scanf("%f", &pCur->_score3);
                break;
            case 6:
                printf("modify name-gender-score1-score2-score3: ");
                scanf("%s %c%f%f%f", pCur->_name, &pCur->_gender, &pCur->_score1, &pCur->_score2, &pCur->_score3);
                break;
            default:
                printf("input error\n");
                break;
            }

            printf("Update success!\n");
            return 0;
        }
    }

    printf("Not found!\n");
    return -1;
}

int func_addUsr(pUsr_t* ppUsrList)
{
    //输入一个用户的信息：name, pwd, mode
    //判断name是否重复，如果重复报错返回，不重复则插入链表中
    Usr_t tmp;
    memset(&tmp, 0, sizeof(tmp));
    
    //录入用户名
    printf("please new usr_name: ");
    scanf("%s", tmp._name);

    for (pUsr_t pCur = *ppUsrList; pCur; pCur = pCur->pNext) {
        if (!strcmp(tmp._name, pCur->_name)) {
            fprintf(stderr, "usr_name is already exist, cannot insert !\n");
            return -1;
        }
    }

    //录入用户密码
    char pwd[30] = {0};
    printf("please input usr_pwd: ");
    scanf("%s", pwd);
    printf("please input usr_pwd again: ");
    scanf("%s", tmp._pwd);

    if (strcmp(pwd, tmp._pwd)) {
        fprintf(stderr, "usr_pwd comparison failed!\n");
        return -1;
    }

    //录入用户权限
    printf("please input usr_mode(0-normal 1-root): ");
    scanf("%d", &tmp._mode);
    if (0 != tmp._mode && 1 != tmp._mode) {
        fprintf(stderr, "usr_mode format error!\n");
        return -1;
    }

    //添加用户
    pUsr_t pNew = (pUsr_t)calloc(1, sizeof(Usr_t));
    memcpy(pNew, &tmp, sizeof(Usr_t));
    pNew->pNext = *ppUsrList;
    *ppUsrList = pNew;
    printf("Add success!\n");
    return 0;
}

int func_eraseUsr(pUsr_t* ppUsrList)
{
    //输入用户名，找到删除
    printf("please input usr_name: ");
    char name[30] = {0};
    scanf("%s", name);

    pUsr_t pCur = *ppUsrList;
    if (!strcmp(name, pCur->_name)) {
        *ppUsrList = pCur->pNext;
    }
    else {
        pUsr_t pPre = pCur;
        pCur = pCur->pNext;

        for (; pCur; pPre = pCur, pCur = pCur->pNext) {
            if (!strcmp(name, pCur->_name)) {
                pPre->pNext = pCur->pNext;
                break;
            }
        }
    }

    if (NULL == pCur) {
        fprintf(stderr, "Not found the usr_name!\n");
        return -1;
    }
    else {
        printf("Delete success!\n");
        free(pCur);
        pCur = NULL;
        return 0;
    }
}

int func_updateUsr(pUsr_t pUsrList)
{
    //输入待修改的usr_name, 若存在则输入修改信息
    printf("please input modify usr_name: ");
    char name[30] = {0};
    scanf("%s", name);

    pUsr_t pCur = NULL;
    for (pCur = pUsrList; pCur; pCur = pCur->pNext) {
        if (!strcmp(name, pCur->_name)) {
            puts("1-modify usr_pwd");
            puts("2-modify usr_mode");

            int option;
            printf("select : ");
            scanf("%d", &option);

            if (1 == option) {
                char tmp[30] = {0};
                char tmp2[30] = {0};
                printf("input usr_pwd: ");
                scanf("%s", tmp);
                printf("input usr_pwd again: ");
                scanf("%s", tmp2);

                if (!strcmp(tmp, tmp2)) {
                    strcpy(pCur->_pwd, tmp);
                }
                else {
                    printf("input error!\n");
                    return -1;
                }
            }
            else if (2 == option) {
                printf("modify usr_mode: ");
                scanf("%d", &pCur->_mode);
            }
            else {
                printf("option error\n");
                return -1;
            }

            printf("Update success!\n");
            return 0;
        }
    }

    printf("Not found!\n");
    return -1;
}

void show_all_stu(pStu_t pStuList)
{
    stu_title();
    for (pStu_t pCur = pStuList; pCur; pCur = pCur->pNext) {
        show_stuInfo(pCur);
    }
}

void show_all_usr(pUsr_t pUsrList)
{
    usr_title();
    for (pUsr_t pCur = pUsrList; pCur; pCur = pCur->pNext) {
        show_usrInfo(pCur);
    }
}

void my_pause()
{
    printf("按任意键继续...\n");
    getchar();
    getchar();
}

int func_findStu(pStu_t pStuList)
{
    int id;
    printf("please input std_id: ");
    scanf("%d", &id);
    
    for (pStu_t pCur = pStuList; pCur; pCur = pCur->pNext) {
        if (id == pCur->_id) {
            system("clear");
            stu_title();
            show_stuInfo(pCur);
            return 0;
        }
    }

    puts("Not found!");
    return -1;
}

int func_findUsr(pUsr_t pUsrList)
{
    char name[30] = {0};
    printf("please input usr_name: ");
    scanf("%s", name);

    for (pUsr_t pCur = pUsrList; pCur; pCur = pCur->pNext) {
        if (!strcmp(name, pCur->_name)) {
            system("clear");
            usr_title();
            show_usrInfo(pCur);
            return 0;
        }     
    }

    puts("Not found!");
    return -1;
}

void show_stuInfo(pStu_t p)
{
    if (p) {
        printf("%d\t%-s\t%-s\t%-5.2f\t%-5.2f\t%-5.2f\n", 
               p->_id, 
               p->_name, 
               p->_gender == '0' ? "女" : "男",
               p->_score1, 
               p->_score2, 
               p->_score3);
    }
}

void show_usrInfo(pUsr_t p) 
{
    if (p) {
        printf("%s\t%s\t%d\n", p->_name, p->_pwd, p->_mode);
    }
}

void stu_title()
{
    puts("ID\tNAME\tGENDER\tSCORE1\tSCORE2\tSCORE3");
}

void usr_title()
{
    puts("NAME\tPWD\tMODE");
}

void menu_0()
{
    puts("              0. exit");
    puts("              1. seach student information by id");
    puts("              2. show all_stu_info");
}

void menu_title()
{
    puts("===============================================================================");
    puts("=             Student    Information    Management    System                  =");
    puts("===============================================================================");
    puts("");
}

void menu_1()
{
    puts("              0. exit");
    puts("");
    puts("              Student Information Func");
    puts("              1. search by id");
    puts("              2. add ");
    puts("              3. update");
    puts("              4. delete ");
    puts("              5. show all");
    puts("");
    puts("              Usr Account Func");
    puts("              6. search by name");
    puts("              7. add ");
    puts("              8. update");
    puts("              9. delete ");
    puts("              10.show all");
    puts("");
}
