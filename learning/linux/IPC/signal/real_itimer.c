#include <func.h>
void sigfunc(int signum) {
    time_t now;
    time(&now);
    printf("%s\n", ctime(&now));
}

int main() {
    signal(SIGALRM, sigfunc);

    struct itimerval real_timer;
    real_timer.it_value.tv_sec = 3;
    real_timer.it_value.tv_usec = 0;
    real_timer.it_interval.tv_sec = 2;
    real_timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &real_timer, NULL);
    /* sigfunc(0); */
    
    while(1);
}
