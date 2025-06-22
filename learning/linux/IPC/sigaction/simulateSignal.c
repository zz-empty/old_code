#include <func.h>
void sigFunc(int signum) {
    printf("%d is comming!\n", signum);
}

int main() 
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigFunc;
    act.sa_flags = SA_RESTART;

    sigaction(SIGINT, &act, NULL);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}

