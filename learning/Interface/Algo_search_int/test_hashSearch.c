#include "search.h"
#include <stdio.h>
#include <string.h>

//数组长度
#define N 10
//数组元素的范围
#define M 100

void test_hashSearch1()
{
    char strArr[N][M] = {
        "hello",
        "tiger",
        "air",
        "monkey",
        "cat",
        "dog",
        "sun",
        "moon",
        "down",
        "up"
    };
    print_chars_arr(strArr, N);
    printf("\n");

    char tmp[M] = {0};
    printf("please input search_str: ");
    scanf("%s", tmp);
    
    int ret = hash_search(strArr, N, tmp);
    if (-1 == ret) {
        printf("Not found %s!\n", tmp);
    }
    else {
        printf("Found %s, pos is %dth on arr\n", strArr[ret], ret + 1);
    }
}


void test_hashSearch2()
{
    char strArr[N][M] = {
        "hello",
        "tiger",
        "air",
        "monkey",
        "cat",
        "dog",
        "sun",
        "moon",
        "down",
        "up"
    };
    print_chars_arr(strArr, N);
    printf("\n");

    char tmp[M] = {0};
    printf("please input search_str: ");
    scanf("%s", tmp);
    
    int ret = hash_search(strArr, N, tmp);
    if (-1 == ret) {
        printf("Not found %s!\n", tmp);
    }
    else {
        printf("Found %s, pos is %dth on arr\n", strArr[ret], ret + 1);
    }
}
