#include <func.h>
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_r");
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_w");

    fd_set rdset;
    fd_set wrset;
    char buf[1024] = {0};
    while(1) {
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(fdr, &rdset);
        FD_SET(fdw, &wrset);

        select(fdw + 1, &rdset, &wrset, NULL, NULL);
        if (FD_ISSET(fdr, &rdset)) {
            int ret = read(fdr, buf, sizeof(buf));
            ERROR_CHECK(ret, -1, "read");
            if (0 == ret) {
                break;
            }

            write(STDOUT_FILENO, "msg from pipe", 13);
            write(STDOUT_FILENO, buf, ret);
        }
        if (FD_ISSET(fdw, &wrset)) {
            int ret = read(STDIN_FILENO, buf, sizeof(buf));
            ERROR_CHECK(ret, -1, "read");
            if (0 == ret) {
                break;
            }

            write(STDOUT_FILENO, "msg from stdin", 14);
            write(fdw, buf, ret);
        }
    }

    close(fdr);
    close(fdw);
    return 0;
}

