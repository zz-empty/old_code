#include <func.h>
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR|O_APPEND);
    ERROR_CHECK(fd, -1, "open");

    printf("pid = %d, uid = %d, euid = %d\n", getpid(), getuid(), geteuid());
    write(fd, "hello", 5);

    close(fd);
    return 0;
}

