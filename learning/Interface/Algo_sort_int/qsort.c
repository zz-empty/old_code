#include <string.h>

//比较字符串数组中的元素
int compare_arr(const void *p1, const void *p2)
{
    const char *pLeft = (const char *)p1;
    const char *pRight = (const char *)p2;
    return strcmp(pLeft, pRight);
}

//比较索引数组中的元素
int compare_index(const void *p1, const void *p2)
{
    const char *pLeft = *(const char **)p1;
    const char *pRight = *(const char **)p2;
    return strcmp(pLeft, pRight);
}

int compare_int(const void *p1, const void *p2)
{
    const int *pLeft = (const int *)p1;
    const int *pRight = (const int *)p2;
    return *pLeft - *pRight;
}
