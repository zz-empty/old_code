#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_r");
    int fdw = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_EXCL, 0600);
    ERROR_CHECK(fdw, -1, "open_w");

    char buf[4096] = {0};
    while(1) {
        memset(buf, 0, sizeof(buf));
        int ret = read(fdr, buf, sizeof(buf));
        if(ret == 0) {
            break;
        }
        write(fdw, buf, strlen(buf));
    }

    close(fdr);
    close(fdw);
    return 0;
}

