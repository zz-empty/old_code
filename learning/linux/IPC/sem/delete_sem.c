#include <func.h>

int main() 
{
    int semid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");

    int ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl_set");

    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;

    semop(semid, &P, 1);
    sleep(8);
    printf("sleep\n");
    semop(semid, &V, 1);

    semctl(semid, 0, IPC_RMID);
    return 0;
}

