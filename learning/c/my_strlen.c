#include <stdio.h>

int myStrlen(char *p) {
    int len = 0;
    while (*p++) {
        len++;
    }
    return len;
}

int main()
{
    printf("please input a str: ");
    char str[200] = {0};
    scanf("%s", str);
    printf("the len of str: %d\n", myStrlen(str));
    return 0;
}

