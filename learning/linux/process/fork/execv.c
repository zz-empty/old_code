#include <func.h>
int main(int argc, char *argv[])
{
    char *arr[] = {"./random", argv[1], argv[2], NULL};
    execv("./random", argv);
    puts("cannot see me");
    return 0;
}

