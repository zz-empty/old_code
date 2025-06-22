#include "../include/head.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (2 != argc) {
        fprintf(stderr, "Usage: %s <confpath>\n", argv[0]);
        return -1;
    }

    const char *conf = argv[1];
    int ret;

    //1. 通过配置文件中的账户和学生信息生成相应的链表
    pStu_t pStuList = NULL;

    return 0;
}

