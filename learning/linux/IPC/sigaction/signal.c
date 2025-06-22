#include <func.h>
void sigfunc(int signum){
    printf("===========ben %d\n", signum);
    sleep(5);
    printf("===========end %d\n", signum);
}

int main() 
{
    struct sigaction act;
    act.sa_handler = sigfunc;
    act.sa_flags = SA_RESTART|SA_NODEFER;
    sigaction(SIGINT, &act, NULL);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    /* printf("ret = %d, buf = %s\n", ret, buf); */
    return 0;
}

