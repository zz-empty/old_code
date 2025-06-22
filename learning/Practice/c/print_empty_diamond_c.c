#include <stdio.h>

void print_empty_diamond(int n) {
    //打印上半部
    for (int i = 1; i <= n; i++) {
        //打印空格
        for (int j = 0; j < n - i; j++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) {
            if (j == 1 || j == 2 * i - 1) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
    //打印下半部
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < n - i; j++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) {
            if (j == 1 || j == 2 * i - 1) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
}
