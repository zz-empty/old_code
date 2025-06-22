#include <func.h>

int main() 
{
    //create sem
    int semid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");
    //init sem
    int ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl_setval");
    //P V
    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;

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
            semop(semid, &P, 1);
            if (p[0] > 0) {
                --p[0];
                ++p[1];
                printf("consuming! p[0] = %d, p[1] = %d\n", p[0], p[1]);
            }
            semop(semid, &V, 1);
        }
    }
    else {
        //producer
        while (1) {
            semop(semid, &P, 1);
            if (p[1] > 0) {
                ++p[0];
                --p[1];
                printf("producing! p[0] = %d, p[1] = %d\n", p[0], p[1]);
            }
            semop(semid, &V, 1);
        }
    }

    shmdt(p);
    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

