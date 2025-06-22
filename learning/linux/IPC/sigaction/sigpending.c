#include <func.h>
void checkSignal(sigset_t *pstatus);
void sigFunc(int signum);
int main() 
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigFunc;
    act.sa_flags = SA_RESTART;
    sigaction(SIGINT, &act, NULL);

    sigset_t status;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT);
    /* checkSignal(&status); */
    sigprocmask(SIG_BLOCK, &mask, NULL);
    /* checkSignal(&status); */

    char buf[128] = {0};
    int ret =read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}
void sigFunc(int signum) {
    printf("%d is comming!\n", signum);
    puts("beg");
    sleep(5);
    puts("end");

    //get block status
    sigset_t status;
    checkSignal(&status);
    //unblock allsig
    sigset_t mask;
    sigemptyset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);
}

void checkSignal(sigset_t *pstatus){
    sigpending(pstatus);
    if (sigismember(pstatus, SIGINT)) {
        printf("SIGINT is blocked!\n");
    }
    else {
        printf("SIGINT is not blocked!\n");
    }
    if (sigismember(pstatus, SIGQUIT)) {
        printf("SIGQUIT is blocked!\n");
    }
    else {
        printf("SIGQUIT is not blocked!\n");
    }
}
