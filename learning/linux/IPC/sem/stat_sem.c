#include <func.h>

int main() 
{
    //create sem
    int semid = semget(1000, 2, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");
    
    struct semid_ds statbuf;
    semctl(semid, 0, IPC_STAT, &statbuf);

    printf("perm = %o\n", statbuf.sem_perm.mode);
    printf("cuid = %d\n", statbuf.sem_perm.cuid);
    printf("nsems = %ld\n", statbuf.sem_nsems);

    statbuf.sem_perm.mode = 0666;
    semctl(semid, 0, IPC_SET, &statbuf);
    semctl(semid, 0, IPC_RMID);
    
    return 0;
}

