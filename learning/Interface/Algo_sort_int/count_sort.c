#include <stdlib.h>
#include <string.h>
void count_sort(int *arr, int len)
{
    if (2 > len) {
        return;
    }

    //建立统计数组，算出arr中的最大值再申请对应大小的数组
    //假设原数组数据都是正数
    int countlen = 0;
    int max = arr[0];
    for (int i = 0; i < len; ++i) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    countlen = max + 1;//统计数组的大小多一点
    
    int *countArr = (int *)malloc(countlen * sizeof(int));
    memset(countArr, 0, sizeof(int) * max);

    //初始化统计数组
    for (int i = 0; i < len; ++i) {
        countArr[arr[i]]++;
    }

    //重建原数组
    int pos = 0;
    for (int i = 0; i < countlen; ++i) {
        //如果统计数组的元素不为0，就将统计数组的下标写入原数组
        while (countArr[i]) {
            arr[pos] = i;
            pos++;
            countArr[i]--;
        }
    }

    free(countArr);
    countArr = NULL;
}
