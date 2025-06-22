#include <func.h>
void func(int num) {
    time_t now;
    time(&now);
    printf("%s\n", ctime(&now));
}

int main() 
{
    signal(SIGPROF, func);
    struct itimerval timer;
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &timer, NULL);

    func(0);
    while(1);
    return 0;
}

