#include <func.h>
void sigFunc(int signum){
    printf("%d is comming!\n", signum);
    puts("beg");
    sleep(5);
    puts("end");
}

int main() 
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigFunc;
    act.sa_flags = SA_RESTART;
    struct sigaction act2;
    memset(&act2, 0, sizeof(act2));
    act2.sa_handler = sigFunc;
    act2.sa_flags = SA_RESTART|SA_NODEFER;

    sigaddset(&act.sa_mask, SIGQUIT);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act2, NULL);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret = %d, buf = %s\n", ret, buf);
    return 0;
}

