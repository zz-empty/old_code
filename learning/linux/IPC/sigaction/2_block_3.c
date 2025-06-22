#include <func.h>
void sigfunc(int signum) {
    printf("==========%d coming\n", signum);
    sleep(3);
    sigset_t status;
    sigpending(&status);
    if (sigismember(&status, SIGQUIT)) {
        printf("%d is suspended!\n", SIGQUIT);
    }
    else {
        printf("%d is not suspend!\n", SIGQUIT);
    }
    printf("==========%d end\n", signum);
}

int main() 
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigfunc;
    act.sa_flags = SA_RESTART;
    sigaddset(&act.sa_mask, SIGQUIT);
    sigaction(SIGINT, &act, NULL);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}

