#include <func.h>
void Daemon() {
    if (fork() != 0) {exit(0);}
    setsid();
    int i;
    chdir("/");
    umask(0);
    printf("pid = %d, ppid = %d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgid(0), getsid(0));
    for (i = 0; i < 10; ++i) {
        close(i);
    }
    while(1);
}
int main()
{
    Daemon();
    for (int i = 0; i < 10; ++i) {
        time_t now;
        time(&now);
        struct tm *p = gmtime(&now);

        syslog(LOG_INFO, "%d %04d:%02d:%02d,", i, p->tm_year + 1900, p->tm_mon + 1, p->tm_mday);
        sleep(2);
    }
    return 0;
}

