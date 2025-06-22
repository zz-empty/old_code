#include <func.h>
int main()
{
    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0) {
        //son write
        close(pipefd[0]);

        write(pipefd[1], "how are you", 11);
    }
    else {
        close(pipefd[1]);
        char buf[1024] = {0};
        read(pipefd[0], buf, sizeof(buf));
        puts(buf);
    }
    return 0;
}

