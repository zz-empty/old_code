#include <stdio.h>

//n的阶乘
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main()
{
    printf("please input a number: ");
    int n;
    scanf("%d", &n);

    printf("the result: %d\n", factorial(n));
    return 0;
}
