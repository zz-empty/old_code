#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//将字符串中的某个字符，替换成另一个字符串, 返回新串
char * change_char(const char *str, char c, char* replace)
{
    if (0 == strlen(str)) {
        printf("string is empty!\n");
        return NULL;
    }
    if (0 == strlen(replace)) {
        printf("No replace!\n");
        return NULL;
    }

    //确定新字符串长度
    int count = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] == c) {
            ++count;
        }
    }
    int newlen = strlen(str) + count * strlen(replace);

    //申请新字符串
    char *newstr = (char*)malloc(newlen * sizeof(char));
    memset(newstr, 0, sizeof(newlen));

    //填充新字符串
    size_t j = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (c == str[i]) {
            strcat(newstr, replace);
            j += strlen(replace);
        }
        else {
            newstr[j++] = str[i];
        }
    } 
    
    return newstr;
}
