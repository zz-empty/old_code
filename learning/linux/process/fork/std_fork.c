#include <func.h>
int main()
{
    for (int i = 0; i < 2; ++i) {
        fork();
        printf("-");
    }
    return 0;
}

