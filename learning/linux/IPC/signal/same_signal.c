#include <func.h>
void sigfunc(int signum) {
    printf("==========beg %d\n", signum);
    sleep(3);
    printf("==========end %d\n", signum);
}

int main() 
{
    signal(SIGINT, sigfunc);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}

