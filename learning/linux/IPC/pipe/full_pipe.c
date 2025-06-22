#include <func.h>
int main()
{
    int fds1[2];
    int fds2[2];
    pipe(fds1);
    pipe(fds2);

    if(0 == fork()) {
        close(fds1[0]);//write fds1
        close(fds2[1]);//read fds2

        char buf[1024] = {0};
        read(fds2[0], buf, sizeof(buf));
        printf("child chat:%s\n", buf);

        write(fds1[1], "what is your name!\n", 18);
        exit(0);
    }
    else {
        close(fds1[1]);//read fds1
        close(fds2[0]);//write fds1

        char buf[1024] = {0};
        write(fds2[1], "how are you!\n", 13);
        read(fds1[0], buf, sizeof(buf));
        printf("parent chat:%s\n", buf);
        wait(NULL);
    }
    return 0;
}

