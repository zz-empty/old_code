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
    return 0;
}

