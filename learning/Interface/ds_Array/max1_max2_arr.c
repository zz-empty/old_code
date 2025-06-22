#include <stdio.h>

//打印数组的最大值和次大值
//需要两个参数，数组第一个元素的指针，最后一个元素的指针
void max1_max2_arr(int *begin, int *end)
{
    if (end < begin) {
        printf("length < 1, dont have max and nextmax!\n");
        return;
    }

    //p1指向最大值，p2指向次大值
    int *p1 = begin;

    //start遍历数组
    int *start = begin + 1;
    //找到最大值
    for (; start <= end; ++start) {
        if (*p1 < *start) {
            p1 = start;
        }
    }

    //将最大值移到第一个位置
    int tmp = *begin;
    *begin = *p1;
    *p1 = tmp;
    //更新p1的指向
    p1 = begin;


    int *p2 = begin + 1;
    //找到次大值
    for (start = p2 + 1; start <= end; ++start) {
        if (*p2 < *start) {
            p2 = start;
        }
    }

    printf("max = %d, nextmax = %d\n", *p1, *p2);
    return;
}
