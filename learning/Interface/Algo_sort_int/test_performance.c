#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if 0
#define N 10
#else
#define N 100000000
#endif

#define M 100

void test_performance()
{
    //申请一段随机序列
    int *arr = (int*)malloc(N * sizeof(int));

    //随机给数组赋值
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % M;
    }

#if 0
    //测试排序的准确度
    print_int_arr(arr, arr + N);
    /* shell_sort(arr, N); */
    /* heap_sort(arr, N); */
    /* count_sort(arr, N); */
    /* qsort(arr, N, sizeof(int), compare_int); */
    print_int_arr(arr, arr + N);
#else
    //测试排序的时间
    time_t begin = time(NULL);
    /* shell_sort(arr, N); */
    /* heap_sort(arr, N); */
    /* count_sort(arr, N); */
    qsort(arr, N, sizeof(int), compare_int);
    time_t end = time(NULL);
    printf("total time : %lds\n", end - begin);
#endif
}
