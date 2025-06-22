#include "../include/head.h"
#include "../include/func.h"
#define STR_LEN 8 //定义随机输出的字符串长度。

int generate_salt(char **salt) {
    char str[STR_LEN+1] = {0};
    int i,flag;
    srand(time(NULL));
    for(i = 0; i < STR_LEN; i ++) {
        flag = rand()%3;
        switch(flag) {
        case 0: str[i] = rand()%26 + 'a'; break;
        case 1: str[i] = rand()%26 + 'A'; break;
        case 2: str[i] = rand()%10 + '0'; break;       
        } 
    }
    *salt = str;

    return 0;
}
