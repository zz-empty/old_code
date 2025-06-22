#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP_INT(a, b) {int tmp = a; a = b; b = tmp;}

int BinarySearch(int *nums, int numsSize, int target) {
    //左闭右闭
    //使用二分查找的数组，必须先升序排序
    int left = 0;
    int right = numsSize - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (target < nums[mid]) {
            right = mid - 1;
        }
        else if (target > nums[mid]) {
            left = mid + 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}

void printArr(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%-3d", arr[i]);
    }
    printf("\n");
}


void bubbleSort(int *arr, int len) {
    for (int i = 0; i < len- 1; i++) {     //i表示最小值放的位置
        for (int j = len - 1; j >= i; j--) { //找最小值要从后往前冒泡
            if (arr[j] < arr[j - 1]) {
                SWAP_INT(arr[j], arr[j - 1]);
            }
        }
    }
}


int main()
{
    //生成一个随机序列
    srand(time(NULL));
    int n = 10;
    int m = 100;
    int *nums = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        nums[i] = rand() % m;
    }
    //升序排序
    printArr(nums, n);
    bubbleSort(nums, n);
    printArr(nums, n);

    //查找元素
    int target = 0;
    while (target != 999) {
        printf("please input a search value: ");
        scanf("%d", &target);

        if (-1 != BinarySearch(nums, n, target)) {
            printf("Yes, it exist\n");
        } else {
            printf("NO, it isn't here\n");
        }
    }
    

    free(nums);
    nums = NULL;
    return 0;
}

