#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//数组长度
#define N 10
//数组元素的范围
#define M 100

void test_binarySearch()
{
    //生成随机序列
    srand(time(NULL));
    int *arr = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % M;
    }
    print_int_arr(arr, arr + N);
    

    printf("\n-------------test binary_search-------------\n");
    int target = arr[0];
    int ret = binary_search(arr, N, target);
    if (-1 == ret) {
        printf("Not found %d!\n", target);
    }
    else {
        printf("Found, %d is %dth!\n", target, ret + 1);
    }
    print_int_arr(arr, arr + N);
}
