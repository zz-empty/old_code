#include <func.h>
int mysystem(const char *command);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int ret = mysystem(argv[1]);
    if (-1 == ret) {
        fprintf(stderr, "Error executing command!\n");
    }
    return 0;
}

int mysystem(const char *command) {
    pid_t pid;
    int status;
    pid = fork();
    
    if (0 == pid) {
        execlp(command, command, (char*)NULL);

        //if execlp return, fail
        fprintf(stderr, "Error: %s\n", command);
        _exit(EXIT_FAILURE);
    }
    else {
        if (waitpid(pid, &status, 0) == -1) {
            fprintf(stderr, "Error:wait failed!\n");
            return -1;
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        else {
            //子进程被信号终止
            fprintf(stderr, "Error: child process teminated by signal %d\n", WTERMSIG(status));
            return -1;
        }
    }
}
