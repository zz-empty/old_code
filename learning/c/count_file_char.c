#include <stdio.h>

int main(int argc, char **argv)
{
    if (2 != argc) {
        fprintf(stderr, "args error\n");
        return -1;
    }

    int ns = 0; //空格数量
    int nt = 0; //制表符数量
    int nl = 0; //行数

    FILE *fp = fopen(argv[1], "r");

    long c = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (' ' == c) {
            ++ns;
        } else if ('\n' == c) {
            ++nl;
        } else if ('\t' == c) {
            ++nt;
        }
    }

    fclose(fp);

    printf("ns = %d, nt = %d, nl = %d\n", ns, nt, nl);
    return 0;
}

