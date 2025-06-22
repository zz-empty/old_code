#ifndef __ARRAY_H__
#define __ARRAY_H__

typedef struct Array
{
    int *_pdata;
    int _size;
    int _capacity;
}Array_t, *pArray_t;

int arr_empty(pArray_t parr);
int arr_full(pArray_t parr);

//初始化    
void arr_init(pArray_t parr, int capacity);
//扩容
void arr_reallocate(pArray_t parr);
//增加
int arr_push_back(pArray_t parr, int val);
int arr_insert(pArray_t parr, int val);
//删除
int arr_erase(pArray_t parr, int val);
int arr_pop_back(pArray_t parr);
//查找
int* arr_find(pArray_t parr, int val);
//修改
int arr_modify(pArray_t parr, int oldval, int newval);


//销毁申请的堆空间
void arr_destory(pArray_t parr);
//展示数组所有元素
void arr_show(pArray_t parr);


#endif
