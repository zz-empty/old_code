#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    char buf[128] = {0};
    read(fd, buf, sizeof(buf));
    puts(buf);
    write(fd, "how old are you", 15);

    close(fd);
    return 0;
}

