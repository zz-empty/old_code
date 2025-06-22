#include <func.h>
#define SIZE 10
/*
1.open file
2.ftruncate file
3.mmap
*/
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    int ret = ftruncate(fd, 10);
    ERROR_CHECK(ret, -1, "ftruncate");
    char *p = (char*)mmap(NULL, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, NULL, "mmap");

    p[0] = 'w';
    p[1] = 'o';
    p[2] = 'r';
    p[3] = 'l';
    p[4] = 'd';

    munmap(p, SIZE);
    close(fd);
    return 0;
}

