#ifndef __HEAD_H__
#define __HEAD_H__

typedef struct Stu
{
    //数据域
    int _id;
    char _name[30];
    char _gender;
    float _score1;
    float _score2;
    float _score3;
    //指针域
    struct Stu *pNext;

}Stu_t, *pStu_t;

typedef struct Usr
{
    //数据域
    char _name[30];
    char _pwd[30];
    int _mode;//权限
    //指针域
    struct Usr *pNext;
}Usr_t, *pUsr_t;

#define RET_CHECK(ret, num, msg)  if (num == ret) { fprintf(stderr, "%s\n", msg); return -1; } 

//主要功能
int init_datas(const char *conf, pUsr_t *ppUsrList, pStu_t *ppStuList);
int login(pUsr_t pUsrList);
void menu(pUsr_t* ppUsrList, pStu_t* ppStuList, int mode);
int update_allInfo(const char *conf, pUsr_t pUsrList, pStu_t pStuList);

//菜单选择

//button 5:
/* void displayUsr(pUsr_t pUsrList); */
//button 10:
/* void displayStu(pStu_t ppStuList); */

#endif
