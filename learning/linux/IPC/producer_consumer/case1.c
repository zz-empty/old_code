#include <func.h>

int main() 
{
    //create shm
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");
    //connect shm
    int *p = (int*)shmat(shmid, NULL, 0);
    ERROR_CHECK(p, (void*)-1, "shmat");

    //resource
    p[0] = 5;//product
    p[1] = 5;//space

    if (0 == fork()) {
        //consumer
        while (1) {
            if (p[0] > 0) {
                --p[0];
                ++p[1];
                printf("consuming! p[0] = %d, p[1] = %d\n", p[0], p[1]);
            }
        }
    }
    else {
        //producer
        while (1) {
            if (p[1] > 0) {
                ++p[0];
                --p[1];
                printf("producing! p[0] = %d, p[1] = %d\n", p[0], p[1]);
            }
        }
    }

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

