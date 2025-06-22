#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max_in_array(int *arr, int len) {
    if (len <= 0) return -1;

    //从头遍历数组，找出最大值
    int max = arr[0];
    for (int i = 0; i < len; i++) {
        if (max < arr[i]) max = arr[i];
    }

    return max;
}

int main()
{
    srand(time(NULL));
    int N = 10;//数组长度
    int M = 100;//数据大小
    int *arr = (int*)malloc(sizeof(int) * N);

    //初始化数组
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % M;
    }

    //遍历数组
    for (int i = 0; i < N; i++) {
        printf("%-3d ", arr[i]);
    }
    printf("\n");

    printf("the max: %d\n", max_in_array(arr, N));

    free(arr);
    arr = NULL;
    return 0;
}

