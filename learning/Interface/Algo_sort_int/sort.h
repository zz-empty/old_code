#ifndef __SORT_H__
#define __SORT_H__

void bubble_sort(int *arr, int len);
void bubble_sort2(int *begin, int *end);
void select_sort(int *arr, int len);
void insert_sort(int *arr, int len);
void shell_sort(int *arr, int len);
void quick_sort(int *arr, int left, int right); //left:首元素下标，right:尾元素下标
void heap_sort(int *arr, int len);
void merge_sort(int *arr, int left, int right);
void count_sort(int *arr, int len);

//比较字符串数组中的元素
int compare_arr(const void *p1, const void *p2);
//比较索引数组中的元素
int compare_index(const void *p1, const void *p2);
//比较int数组中的元素
int compare_int(const void *p1, const void *p2);


void print_int_arr(int *begin, int *end);
void print_chars_arr(char (*arr)[100], int len);
void print_index_arr(char **ppArr, int len);

#endif
