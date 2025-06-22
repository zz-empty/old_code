#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b) {int tmp = a; a = b; b = tmp;}

//冒泡排序
void bubbleSort(int *arr, int len, int flag) {
    //flag != 0 表示升序排列，
    //flag == 0 表示降序排列
    if (flag) {
        //每轮查找，找出最大值放最后面，找完之后缩小数据的规模
        for (int i = len - 1; i >= 0; i--) { //i表示找多少次最大值
            for (int j = 0; j < i; j++) {
                if (arr[j] > arr[j + 1]) {
                    SWAP(arr[j], arr[j + 1]);
                }
            }
        }
    } else {
        //每轮查找，将最大值放最前面，然后缩小数据规模
        for (int i = 0; i < len; i++) { 
            for (int j = len - 1; j > i; j--) {
                if (arr[j] > arr[j - 1]) {
                    SWAP(arr[j], arr[j - 1]);
                }
            }
        }
    }
}

//得到数组中的最大值
int maxOfArray(int *arr, int len) {
    if (len <= 0) return -1;

    //从头遍历数组，找出最大值
    int max = arr[0];
    for (int i = 0; i < len; i++) {
        if (max < arr[i]) max = arr[i];
    }

    return max;
}

//生成一个随机数组
int* randonArr(int N, int M) {
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
    bubbleSort(arr, N, 0);
    printArr(arr, N);

    //释放数组所占的堆空间
    free(arr);
    arr = NULL;
    return 0;
}
