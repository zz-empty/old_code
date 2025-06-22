#include <stdlib.h>

//qsort的第四个参数
int compare_int(const void *p1, const void *p2)
{
    const int *pLeft = (const int *)p1;
    const int *pRight = (const int *)p2;
    return *pLeft - *pRight;
}

//输入：数组地址，数组长度，待查找元素
//输出：查找元素的下标，没找到就返回-1
int binary_search(int *arr, int len, int target)
{
    if (2 > len) {
        return -1;
    }

    //先排序再查找
    qsort(arr, len, sizeof(int), compare_int);    

    int left = 0;   //首元素下标
    int right = len - 1;    //尾元素下标

    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            //数组中间节点大于target，去左边找
            right = mid - 1;
        }
        else if (arr[mid] < target) {
            //数组中间节点小于target，去右边找
            left = mid + 1;
        }
        else {
            //中间节点等于target，返回下标
            return mid;
        }
    }

    //没找到
    return -1;
}
