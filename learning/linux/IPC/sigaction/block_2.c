#include <func.h>
void sigfunc(int signum) {
    printf("==========beg %d\n", signum);

    printf("===========end %d\n", signum);
}

int main() 
{
    //block SIGINT
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, 0);

    signal(SIGINT, sigfunc);
    sleep(5);
    sigset_t status;
    sigpending(&status);
    if (sigismember(&status, SIGINT)) {
        printf("--------------%d is blocked\n", SIGINT);
    }
    else {
        printf("--------------%d is not blocked\n", SIGINT);
    }
    if (sigismember(&status, SIGQUIT)) {
        printf("--------------%d is blocked\n", SIGQUIT);
    }
    else {
        printf("--------------%d is not blocked\n", SIGQUIT);
    }
    //unblock all
    sigemptyset(&mask);
    sigprocmask(SIG_SETMASK, &mask, 0);


    char buf[128] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    return 0;
}

