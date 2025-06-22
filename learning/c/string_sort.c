#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

void sort_str(char (*shop)[MAXSIZE], int len) {
    for (int j = len - 1; j >= 0; j--) {
        for (int i = 0; i < j; i++) {
            if (strcmp(shop[i], shop[i + 1]) > 0) {
                //前面的大，就交换
                char tmp[MAXSIZE];
                strcpy(tmp, shop[i]);
                strcpy(shop[i], shop[i + 1]);
                strcpy(shop[i + 1], tmp);
            }
        }
    }
}

void printStrArr(char (*shop)[MAXSIZE], int len) {
    for (int i = 0; i < len; i++) {
        puts(shop[i]);
    }
}

int main()
{
    //排序字符串数组
    char shop[][MAXSIZE] = {"hello", "cat", "sky", "land", "brand", "air"};
    int len = sizeof(shop) / MAXSIZE;

    printStrArr(shop, len);
    sort_str(shop, len);
    printf("-----------After sort----------\n");
    printStrArr(shop, len);


    return 0;
}

