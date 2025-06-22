#include <stdio.h>

int main()
{
    //打印九九乘法表
    //第几行，就打几列

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {  //从1开始，打印到第i列
            printf("%dx%d=%-3d", j, i, i * j);
        }
        printf("\n");
    }
    return 0;
}

