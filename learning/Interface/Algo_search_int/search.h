#ifndef __SEARCH_HPP
#define __SEARCH_HPP

#define M 100

int binary_search(int *arr, int len, int target);
int hash_search(char (*pArr)[100], int len, char *target);

//打印
void print_int_arr(int *begin, int *end);
void print_chars_arr(char (*arr)[M], int len);


#endif
