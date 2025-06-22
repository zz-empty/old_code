#include <func.h>
#define COUNT 200000

int main() 
{
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");
    int *p = (int*)shmat(shmid, NULL, 0);
    p[0] = 0;

    if (fork() == 0) {
        for (int i = 0; i < COUNT; ++i) {
            p[0]++;
        }
        exit(0);
    }
    else {
        for (int i = 0; i < COUNT; ++i) {
            p[0]++;
        }
        wait(NULL);
        printf("Total = %d\n", p[0]);
    }

    shmdt(p);
    return 0;
}

