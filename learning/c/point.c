#include <stdio.h>

int main()
{
    int i = 4;
    int *p = &i;
    /* printf("++*p = %d\n", ++*p); */
    /* printf("i = %d\n", i); */
    /* printf("*++p = %d\n", *++p); */
    /* printf("i = %d\n", i); */
    /* printf("*p++ = %d\n", *p++); */
    /* printf("*p = %d\n", *p); */

    int arr[] = {4, 3, 7, 5};
    p = arr;
    /* printf("p[0]++ = %d\n", p[0]++); */
    printf("++p[0] = %d\n", ++p[0]);
    printf("*p = %d\n", *p);
    return 0;
}

