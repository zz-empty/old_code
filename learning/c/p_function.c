#include <stdio.h>

typedef int (*Two)(int, int);

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int main()
{
    Two p = add;
    printf("p(2, 3) = %d\n", p(2, 3));

    p = sub;
    printf("p(2, 3) = %d\n", p(2, 3));

    return 0;
}

