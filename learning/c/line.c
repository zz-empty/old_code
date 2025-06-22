#include <stdio.h>

int main()
{
    int c = 0;  //读取的字符
    int l = 0;  //行数

    while( (c = getchar()) != EOF) {
        if (c == '\n') {
            ++l;
        }
    }
    printf ("l = %d\n", l);
    return 0;
}

