#include <func.h>

int main() 
{
    int semid = semget(1000, 2, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");

    int ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl");
    ret = semctl(semid, 1, SETVAL, 9);
    ERROR_CHECK(ret, -1, "semctl");
    printf("%d semval = %d, %d\n", semid, semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));

    unsigned short val[2] = {2, 3};
    ret = semctl(semid, 0, SETALL, val);
    ERROR_CHECK(ret, -1, "semctl_all");
    printf("%d semval = %d, %d\n", semid, semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));

    semctl(semid, 0, IPC_RMID);
    return 0;
}

