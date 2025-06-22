#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b) {int tmp = a; a = b; b = tmp;}

//逆转链表
void reverse(int *arr, int len) {
    int *start = arr;
    int *end = arr + len - 1;
    while (start < end) {
        SWAP(*start, *end);
        start++;
        end--;
    }
}

//生成一个随机数组
int* randonArr(int N, int M) {
    if (N <= 0) return NULL;

    srand(time(NULL));
    int *arr = (int*)malloc(sizeof(int) * N);

    //初始化数组
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % M;
    }

    return arr;
}

//打印数组
void printArr(int *arr, int len) {
    if (len <= 0) return;

    for (int i = 0; i < len; i++) {
        printf("%-3d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    //生成一个随机数组
    int N = 10;//数组长度
    int M = 100;//数据大小
    int *arr = randonArr(N, M);
    printArr(arr, N);

    //对数组的操作
    reverse(arr, N);
    printArr(arr, N);

    //释放数组所占的堆空间
    free(arr);
    arr = NULL;
    return 0;
}
