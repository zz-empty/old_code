#include <func.h>
void sigfunc(int signum) {
    printf("  %d is comming! ", signum);
    printf("beg\n");
    sleep(3);
    printf("%d,end\n", signum);
}
void func(int signum) {
    printf("============beg %d\n", signum);
    sleep(9);
    printf("============end %d\n", signum);
}

int main() 
{
    signal(SIGINT, sigfunc);
    signal(SIGQUIT, func);

    char buf[256] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}

