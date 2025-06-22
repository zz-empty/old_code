#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_WRONLY);
    ERROR_CHECK(fd, -1, "open");

    int val = 10000;
    write(fd, &val, sizeof(val));
    ERROR_CHECK(fd, -1, "write");

    close(fd);
    return 0;
}

