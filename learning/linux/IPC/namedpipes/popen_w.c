#include <func.h>
int main()
{
    FILE *fp = popen("./sub", "w");
    fwrite("10000 10099", 1, 11, fp);
    pclose(fp);
    return 0;
}

