#include "qq.h"

int main() 
{
    printf("pid = %d\n", getpid());
    pids[1] = getpid();
    printf("pids[1] = %d\n", pids[1]);
    int ret;
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");

    char *p = (char*)shmat(shmid, NULL, 0);
    ERROR_CHECK(p, (void*)-1, "shmat");

    int semid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");

    ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl_set");
    struct sembuf P, V;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    V.sem_num = 0; 
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;


    while(1) {
        if (p[0] != '\0') {
            semop(semid, &P, 1);
            puts(p);
            memset(p, 0, 4096);
            semop(semid, &V, 1);
        }
    }

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

