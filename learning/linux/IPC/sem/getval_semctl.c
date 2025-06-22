#include <func.h>

int main() 
{
    //create sem
    int semid = semget(1001, 1, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");
    //init sem
    int ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl");

    int val = semctl(semid, 0, GETVAL);
    ERROR_CHECK(val, -1, "semctl");
    printf("val = %d\n", val);

    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    ret = semop(semid, &P, 1);
    ERROR_CHECK(ret, -1, "semop");
    val = semctl(semid, 0, GETVAL);
    printf("val = %d\n", val);

    //delete sem
    semctl(semid, 0, IPC_RMID, NULL);
    return 0;
}

