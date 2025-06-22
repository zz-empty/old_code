#include <func.h>
int main()
{
    if (fork() == 0) {
        printf("child, pid = %d, ppid = %d\n", getpid(), getppid());
        /* while(1); */
        exit(20);
    }
    else {
        printf("I am parent!\n");

        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("child exit with status %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("child was terminated by signal %d\n", WTERMSIG(status));
        }
    }
    return 0;
}

