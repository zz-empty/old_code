#include <func.h>
int main()
{
    int lhs, rhs;
    scanf("%d%d", &lhs, &rhs);

    printf("I am child process, %d - %d = %d\n", lhs, rhs, lhs-rhs);
    return 0;
}

