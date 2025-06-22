#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arr_init(pArray_t parr, int capacity)
{
    parr->_pdata = (int*)calloc(capacity, sizeof(int));
    parr->_size = 0;
    parr->_capacity = capacity;
}

void arr_show(pArray_t parr)
{
    if (!arr_empty(parr)) {
        printf("arr_data: ");
        for (int i = 0; i < parr->_size; ++i) {
            printf("%d ", parr->_pdata[i]);
        }
        printf("\n");
        printf("arr_size: %d\n", parr->_size);
        printf("arr_capacity: %d\n", parr->_capacity);
    }
    else {
        printf("arr is empty!\n");
    }
}

//扩容
void arr_reallocate(pArray_t parr)
{
    if (arr_full(parr)) {
        //保存旧数据
        Array_t tmp = *parr;
        
        //确定新容量
        int newcapacity = 2 * tmp._capacity == 0 ? 1 : 2 * tmp._capacity;
        //申请新空间
        parr->_pdata = (int *)calloc(newcapacity, sizeof(int));
        //拷贝数据
        memcpy(parr->_pdata, tmp._pdata, tmp._size * sizeof(int));
        parr->_capacity = newcapacity;

        //释放旧空间
        free(tmp._pdata);
        tmp._pdata = NULL;
    }
}

//增加, 有序
int arr_push_back(pArray_t parr, int val)
{
    if (arr_full(parr)) {
        arr_reallocate(parr);
    }

    //插在末尾
    parr->_pdata[parr->_size++] = val;

    return 0;
}

int arr_insert(pArray_t parr, int val)
{
    if (arr_full(parr)) {
        arr_reallocate(parr);
    }
   
    //空表时直接插入
    //非空时，从后往前找到第一个小于等于插入值的，放其后，否则元素后移
    //找不到时，放首位
    
    if (arr_empty(parr)) {
        parr->_pdata[parr->_size++] = val;
    }
    else {
        int i = parr->_size - 1;
        for (; i >= 0; --i) {
            if (parr->_pdata[i] > val) {
                parr->_pdata[i + 1] = parr->_pdata[i];
            }
            else {
                parr->_pdata[i + 1] = val;
                parr->_size++;
                break;
            }
        }

        if (val < parr->_pdata[0]) {
            parr->_pdata[0] = val;
            parr->_size++;
        }
    }

    return 0;
}


//删除
int arr_erase(pArray_t parr, int val)
{
    //空表
    if (arr_empty(parr)) {
        printf("Arr is empty, cannot erase!\n");
        return -1;
    } 

    //从头遍历，如果等于val, ++count, --size, 否则 arr[i + count] = arr[i]
    int count = 0;
    int size = parr->_size;
    for (int i = 0; i < parr->_size; ++i) {
        if (val == parr->_pdata[i]) {
            ++count;
            --size;
        }
        else {
            parr->_pdata[i - count] = parr->_pdata[i];
        }
    }

    if (0 == count) {
        printf("Not found, cannot erase!\n");
        return -1;
    }
    else {
        parr->_size = size;
        return 0;
    }
}

int arr_pop_back(pArray_t parr)
{
    if (arr_empty(parr)) {
        fprintf(stderr, "array is empty, cannot delete elem!\n");
        return -1;
    }

    parr->_size--;
    return 0;
}

//查找
int* arr_find(pArray_t parr, int val)
{
    if (!arr_empty(parr)) {
        for (int i = 0; i < parr->_size; ++i) {
            if (val == parr->_pdata[i]) {
                return &parr->_pdata[i];
            }
        }        
    }
    
    return NULL;
}

//修改
int arr_modify(pArray_t parr, int oldval, int newval)
{
    //空表
    if (arr_empty(parr)) {
        printf("arr is empty!\n");
        return -1;
    }

    int *ret = arr_find(parr, oldval);
    if (NULL == ret) {
        printf("Not found, cannot modify!\n");
        return -1;
    }
    else {
        *ret = newval;
        return 0;
    }
}

int arr_empty(pArray_t parr)
{
    return parr->_size == 0;
}

int arr_full(pArray_t parr)
{
    return parr->_size == parr->_capacity;
}

void arr_destory(pArray_t parr)
{
    if (parr->_pdata) {
        free(parr->_pdata);
        parr->_pdata = NULL;
    }
}
