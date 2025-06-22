#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0600);
    ERROR_CHECK(fd, -1, "open");

    if (fork() == 0) {
        printf("I am chile process!\n");
        write(fd, "hello", 5);
        exit(0);
    }
    else {
        printf("I am parent process!\n");
        write(fd, "world", 5);
        wait(NULL);
    }

    return 0;
}

