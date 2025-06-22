#include "sort.h"
#include <stdio.h>
#include <stdlib.h>


void test_bubbleSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    /* bubble_sort(arr, len); */
    bubble_sort2(arr, arr + len);
    print_int_arr(arr, arr + len);
}

void test_selectSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    select_sort(arr, len);
    print_int_arr(arr, arr + len);
}

void test_insertSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    insert_sort(arr, len);
    print_int_arr(arr, arr + len);
}

void test_shellSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    shell_sort(arr, len);
    print_int_arr(arr, arr + len);
}

void test_quickSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    quick_sort(arr, 0, len - 1);
    print_int_arr(arr, arr + len);
}

void test_qsort1()
{
    //直接排序字符串数组
    char wordbook[][100] = {
        "hello",
        "hero",
        "abandon",
        "wukong",
        "loong",
        "angle",
        "pretty",
        "handsome",
        "vector"
    };
    int len = sizeof(wordbook) / sizeof(wordbook[0]);
    print_chars_arr(wordbook, len);

    qsort(wordbook, sizeof(wordbook) / sizeof(wordbook[0]), sizeof(wordbook[0]), compare_arr);

    printf("\n-----------------------\n");
    print_chars_arr(wordbook, len);
}

void test_qsort2()
{
    //排序索引数组
    char wordbook[][100] = {
        "hello",
        "hero",
        "abandon",
        "wukong",
        "loong",
        "angle",
        "pretty",
        "handsome",
        "vector"
    };
    int len = sizeof(wordbook) / sizeof(wordbook[0]);
    printf("原数组-----------------------\n");
    print_chars_arr(wordbook, len);

    //构建索引数组
    char **pArr = (char**)calloc(len, sizeof(char*));
    //初始化索引数组
    for (int i = 0; i < len; ++i) {
        pArr[i] = wordbook[i];
    }
    printf("\n索引数组-----------------------\n");
    print_index_arr(pArr, len);

    qsort(pArr, len, sizeof(char*), compare_index);

    printf("\n原数组-----------------------\n");
    print_chars_arr(wordbook, len);
    printf("\n索引数组-----------------------\n");
    print_index_arr(pArr, len);

    //释放索引数组
    free(pArr);
    pArr = NULL;
}

void test_heapSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    heap_sort(arr, len);
    print_int_arr(arr, arr + len);
}

void test_mergeSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    merge_sort(arr, 0, len - 1);
    print_int_arr(arr, arr + len);
}

void test_countSort()
{
    int arr[] = { 4, 3, 9, 2, 7, 8, 0, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    print_int_arr(arr, arr + len);
    count_sort(arr, len);
    print_int_arr(arr, arr + len);
}

