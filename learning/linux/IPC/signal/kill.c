#include <func.h>

int main(int argc, char *argv[]) 
{
    //./kill -9 pid
    ARGS_CHECK(argc, 3);
    int sig = atoi(argv[1] + 1);
    pid_t pid = atoi(argv[2]);
    kill(pid, sig);
    return 0;
}

