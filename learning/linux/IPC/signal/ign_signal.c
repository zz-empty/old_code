#include <func.h>
void sigFunc(int signum) {
    printf("%d is comming!\n", signum);
}

int main() 
{
    /* signal(SIGINT, SIG_IGN); */
    signal(SIGINT, sigFunc);
    signal(SIGQUIT, sigFunc);

    while(1);
    return 0;
}

