#include <func.h>
int main()
{
    execl("./add" ,"./add", "12", "23", NULL);
    printf("you can't see me");
    return 0;
}

