#include <stdio.h>
#include <string.h>

void str_divide_num_alp(char *str)
{
    //干掉换行符
    if ('\n' == str[strlen(str)- 1]) {
        str[strlen(str) - 1] = '\0';
    }

    //分成前数字后字母, 遇到数字，将数字前的所有字母往后移
    size_t j = 0;//指向字母
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            //保存str[i], 将j到i的所有元素往后移
            char tmp = str[i];
            for (size_t k = i; k > j; --k) {
                str[k] = str[k - 1];
            }
            str[j++] = tmp;
        }
    }
}
