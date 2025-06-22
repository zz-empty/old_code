#include <stdio.h>

//打印int数组
void print_int_arr(int *begin, int *end)
{
    int *start = begin;
    for (; start != end; ++start) {
        printf("%d ", *start);
    }
    printf("\n");
}

void print_chars_arr(char (*arr)[100], int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%s\n", arr[i]);
    }
}

void print_index_arr(char **ppArr, int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%s\n", ppArr[i]);
    }
}
