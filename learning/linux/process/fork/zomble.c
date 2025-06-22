#include <func.h>
int main()
{
    if (fork() == 0) {
        printf("child!\n");
        return 0;
    }
    else {
        printf("parent!\n");
        while(1);
    }
    return 0;
}

