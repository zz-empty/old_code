#include <func.h>

int setNoBlock(int fd) {
    int status = fcntl(fd, F_GETFL);
    status |= O_NONBLOCK;
    fcntl(fd, F_SETFL, status);
    return 0;
}

int main(int argc, char *argv[]) 
{
    char buf[64] = {0};
    setNoBlock(STDIN_FILENO);
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("buf = %s\n", buf);
    return 0;
}

