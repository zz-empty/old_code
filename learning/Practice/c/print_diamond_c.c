#include <stdio.h>

void print_diamond(int n) 
{
    //打印上半部
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n - i; j++) printf(" ");
        for (int j = 0; j < i; j++) {
            printf("*");
            if (j != i - 1) printf(" ");
        }
        printf("\n");
    }
    //打印下半部
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < n - i; j++) printf(" ");
        for (int j = 0; j < i; j++) {
            printf("*");
            if (j != i - 1) printf(" ");
        }
        printf("\n");
    }
}
