#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    printf("key = %d\n", ftok(argv[1], 0));
    return 0;
}

