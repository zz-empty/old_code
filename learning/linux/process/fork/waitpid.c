#include <func.h>
int main()
{
    pid_t pid = fork();
    int status;
    if (0 == pid) {
        printf("child ,pid = %d, ppid = %d\n", getpid(), getppid());
        while(1);
        exit(0);
    }
    else {
        printf("parent pid = %d\n", getpid());
        
        while(1) {
            int ret = waitpid(pid, &status, WNOHANG);
            if (0 == ret) {
                sleep(3);
                printf("No child status was changed\n");
            }
            else {
                if (WIFEXITED(status)) {
                    printf("child exit with status %d\n", WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status)) {
                    printf("child was teminated by signal %d\n", __WTERMSIG(status));
                }
                break;
            }
        }
    }
    return 0;
}

