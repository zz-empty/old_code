#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    if (2 != argc) {
        fprintf(stderr, "Args error!\n");
        return -1;
    }

    int num = atoi(argv[1]);
    if (num & 1) {
        printf("yes!\n");
    } else {
        printf("no!\n");
    }
    return 0;
}

