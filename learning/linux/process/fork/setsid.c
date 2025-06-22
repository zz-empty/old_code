#include <func.h>
int main()
{
    if (fork() == 0) {
        printf("before child, pid = %d, ppid = %d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgid(0), getsid(0));
        setsid();
        printf("after child, pid = %d, ppid = %d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgid(0), getsid(0));
        exit(0);
    }
    else {
        printf("parent, pid = %d, ppid = %d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgid(0), getsid(0));
        wait(NULL);
    }
    return 0;
}

