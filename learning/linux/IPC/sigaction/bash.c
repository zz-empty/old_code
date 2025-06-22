#include <func.h>
void sigfunc(int signum) {
    printf("%s\n", getcwd(NULL, 0));
}

int main() 
{
    struct sigaction act;
    act.sa_handler = sigfunc;
    act.sa_flags = SA_RESTART;
    sigaction(SIGINT, &act, NULL);

    char buf[128] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    if (0 == fork()) {
        setpgid(0, 0);
        execl(buf, buf, NULL);
    }
    else {
        wait(NULL);
        while(1) {
            memset(buf, 0, sizeof(buf));
            char *ret = getcwd(NULL, 0);
            printf("%s@%s:", getpwuid(getuid())->pw_name,ret);
            read(STDIN_FILENO, buf, sizeof(buf));
            if (strcmp(buf, "exit")) {
                exit(0);
            }
        }
    }
    return 0;
}

