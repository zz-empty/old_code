#include <func.h>
#define N 1000000

int main() 
{
    //get sem
    int semid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");

    //set sem val
    int ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl");

    //P V operation
    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;

    //get shm
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");
    //connect shm
    int *p = (int*)shmat(shmid, NULL, 0);
    ERROR_CHECK(p, (void*)-1, "shmat");

    p[0] = 0;
    //start time
    struct timeval beg, end;
    gettimeofday(&beg, NULL);
    if (0 == fork()) {
        for (int i = 0; i < N; ++i) {
            semop(semid, &P, 1);
            p[0]++;
            semop(semid, &V, 1);
        }
        exit(0);
    }
    else {
        for (int i = 0; i < N; ++i) {
            semop(semid, &P, 1);
            p[0]++;
            semop(semid, &V, 1);
        }
        wait(NULL);
        //end time
        gettimeofday(&end, NULL);
        long timeTotal = (end.tv_sec - beg.tv_sec) * 1000000 + end.tv_usec - beg.tv_usec;
        printf("timeTotal = %ldus, timeAvg = %.2lfs\n", timeTotal, (double)timeTotal / 4000000);//four operation

        printf("Result = %d\n", p[0]);
    }

    //release shm
    ret = shmdt(p);
    ERROR_CHECK(ret, -1, "shmdt");
    //delete shm
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

