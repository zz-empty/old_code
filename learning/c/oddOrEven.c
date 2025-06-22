#include <stdio.h>

void addOrEven()
{
    printf("input a integer: ");
    int num;
    scanf("%d", &num);

    if (num % 2 == 0) {
        printf("Even!\n");
    } else {
        printf("Odd!\n");
    }
}

