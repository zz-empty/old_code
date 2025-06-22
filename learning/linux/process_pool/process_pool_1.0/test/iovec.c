#include <func.h>

int main(int argc, char *argv[]) 
{
    struct iovec iov[2];
    memset(iov, 0, sizeof(iov));

    char buf1[16] = "hello";
    char buf2[16] = "world";
    iov[0].iov_base = buf1;
    iov[0].iov_len = sizeof(buf1);
    iov[1].iov_base = buf2;
    iov[1].iov_len = sizeof(buf2);

    writev(STDOUT_FILENO, iov, 2);
    
    return 0;
}

