#include <func.h>
void sigFunc(int signum) {
    printf("%d is commming!\n", signum);
}

int main() 
{
    struct sigaction act;
    act.sa_handler = sigFunc;
    act.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &act, NULL);

    sigset_t oldmask, blkmask;
    sigemptyset(&blkmask);
    sigaddset(&blkmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &blkmask, &oldmask);

    alarm(3);
    sigsuspend(&oldmask);
    return 0;
}

