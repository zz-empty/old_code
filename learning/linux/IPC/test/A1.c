#include <func.h>
int main()
{
    int semid = semget(1000,1,IPC_CREAT | 0600);
    semctl(semid,0,SETVAL,1);
    struct sembuf P;
    P.sem_op = -1;
    P.sem_num = 0;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_op = 1;
    V.sem_num = 0;
    V.sem_flg = SEM_UNDO;

    int shmid = shmget(1000,4096,IPC_CREAT|0600);
    char* p = (char*)shmat(shmid,NULL,0);
    char* msg = p + 20;
    int* proc = (int*)p;
    proc[2] = getpid();
    int* toprint = proc + 4;
    while(1)
    {
        if(*toprint == 1)
        {
            semop(semid,&P,1);
            printf("%s",msg);
            *toprint = 0;
            semop(semid,&V,1);
        }
    }
}
