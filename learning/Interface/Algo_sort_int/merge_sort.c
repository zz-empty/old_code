#include <stdlib.h>
#include <string.h>

#if 1
void merge(int *arr, int left, int mid, int right)
{
    //在原数组上操作,类似插入排序，将后面的数据，有序插入进前面的数组
    for (int i = mid + 1; i <= right; ++i) {
        //保存来牌
        int val = arr[i];
        //给来牌腾位置
        int j = i - 1;
        for (; j >= left; --j) {
            if (arr[j] > val) {
                arr[j + 1] = arr[j];
            }
            else {
                break;
            }
        }
        //插入来牌
        arr[j + 1] = val;
    }
}

#else

void merge(int *arr, int left, int mid, int right) 
{
    //用辅助数组进行合并
    int len = right - left + 1;
	int *b = (int*)malloc(len * sizeof(int));
	memcpy(b, arr, len * sizeof(int));

	int i = left;
	int j = mid + 1;
	int k = left;

	for (; i <= mid && j <= right; ++k) {
		if (b[i] < b[j]) {
			arr[k] = b[i++];
		}
		else {
			arr[k] = b[j++];
		}
	}
	while (i <= mid) {
		arr[k++] = b[i++];
	}
	while (j <= right) {
		arr[k++] = b[j++];
	}
}

#endif

void merge_sort(int *arr, int left, int right) 
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        //合并有序数组
        merge(arr, left, mid, right);
    }
}
