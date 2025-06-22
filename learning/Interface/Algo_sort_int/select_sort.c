#include <stdio.h>
void select_sort(int *arr, int len)
{
    //每次遍历找出最大值的下标，与最后交换
    //i 表示最大值的下标
    for (int i = len - 1; i > 1; --i) {
        int max = 0;    //从第一个开始找
        for (int j = 1; j < i; ++j) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        printf("max = %d\n", arr[max]);

        //将本轮最大值放最后
        int tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
    }
}
