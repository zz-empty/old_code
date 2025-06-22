#ifndef __HEAD_H__
#define __HEAD_H__

//学生数据结构
typedef struct Stu {
    //数据域
    int _id;
    char _name[30];
    char _gander;
    float s1;
    float s2;
    float s3;
    //指针域
    struct Stu *_pNext;
}Stu_t, *pStu_t;



#endif
