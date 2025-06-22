#include <func.h>
int main()
{
    if (fork() == 0) {
        printf("child!\n");
        while(1);
    }
    else {
        printf("parent!\n");
        return 0;
    }
    return 0;
}

