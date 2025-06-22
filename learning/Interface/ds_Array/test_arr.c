#include "array.h"
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    //申请数组
    pArray_t arr = (pArray_t)malloc(sizeof(Array_t));
    arr_init(arr, 10);
    arr_show(arr);

    for (int i = 0; i < 10; ++i) {
        arr_push_back(arr, i + 3);
    }
    arr_show(arr);

    printf("\n---------test arr_insert------------\n");
    arr_insert(arr, 1);
    arr_insert(arr, 10);
    arr_show(arr);

    printf("\n---------test arr_erase------------\n");
    arr_erase(arr, 3);
    arr_erase(arr, 10);
    arr_show(arr);

    printf("\n---------test arr_erase------------\n");
    arr_pop_back(arr);
    arr_pop_back(arr);
    arr_show(arr);


    //释放数组
    arr_destory(arr);
    free(arr);
    arr = NULL;

    return 0;
}

