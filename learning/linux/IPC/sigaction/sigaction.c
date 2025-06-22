#include <func.h>
void sigFunc(int signum, siginfo_t *p, void *p1) {
    printf("%d is comming!\n", signum);
}

int main() 
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = sigFunc;
    act.sa_flags = SA_SIGINFO|SA_RESTART|SA_RESETHAND;
    
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}

