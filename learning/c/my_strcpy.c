#include <stdio.h>

void myStrcpy(char *dest, const char *src) {
    while ((*dest++ = *src++));
}

int main()
{
    printf("please input a src: ");
    char src[30] = "";
    scanf("%s", src);
    char dest[30] = "";
    myStrcpy(dest, src);
    printf("dest:%s, src:%s\n", dest, src);
    return 0;
}

