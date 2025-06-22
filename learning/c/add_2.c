#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (3 != argc) {
        fprintf(stderr, "Usage: %s <number1> <number2> \n", argv[0]);
        return -1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Sum: %d\n", num1 + num2);
    return 0;
}

