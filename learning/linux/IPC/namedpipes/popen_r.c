#include <func.h>
int main()
{
    FILE *fp = popen("./print", "r");

    char buf[1024] = {0};
    fread(buf, 1, sizeof(buf), fp);

    puts("msg from pipe!");
    puts(buf);

    pclose(fp);
    return 0;
}

