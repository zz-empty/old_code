#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#define ARGS_CHECK(argc, num) {if(argc != num) {fprintf(stderr, "args error!\n"); return -1;}}
#define ERROR_CHECK(ret, num, msg) {if(ret == num) {perror(msg);return -1;}}

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    printf("uid = %d, euid = %d\n", getuid(), geteuid());

    int fd = open(argv[1], O_WRONLY|O_CREAT, 0600);
    ERROR_CHECK(fd, -1, "open");
    
    int ret = write(fd, "hello", 5);
    ERROR_CHECK(ret, -1, "write");
    return 0;
}

