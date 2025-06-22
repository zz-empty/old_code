#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int searchInArray(int *arr, int len, int target) {
    //找到就返回下标，没找到就返回-1    
    for (int i = 0; i < len; i++) {
        if (target == arr[i]) {
            return i;
        }
    }
    return -1;
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
    int N = 30;//数组长度
    int M = 100;//数据大小
    int *arr = randonArr(N, M);
    printArr(arr, N);

    //对数组的操作
    int target = rand() % M;
    printf("target: %d\n", target);
    int result = searchInArray(arr, N, target);
    if (-1 != result) {
        printf("Find! the pos is %d\n", result);
    } else {
        printf("Not Find!\n");
    }

    //释放数组所占的堆空间
    free(arr);
    arr = NULL;
    return 0;
}
