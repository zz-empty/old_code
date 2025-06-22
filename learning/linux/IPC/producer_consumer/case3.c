#include <func.h>

int main() 
{
    //create sem
    int semid = semget(1000, 2, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");
    //init sem
    unsigned short val[2] = {5, 5};//val[0]:product  val[1]:space
    int ret = semctl(semid, 0, SETALL, val);
    ERROR_CHECK(ret, -1, "semctl_setval");

    //produce
    struct sembuf produce[2];
    produce[0].sem_num = 0;
    produce[0].sem_op = 1;
    produce[0].sem_flg = SEM_UNDO;
    produce[1].sem_num = 1;
    produce[1].sem_op = -1;
    produce[1].sem_flg = SEM_UNDO;
    //cousume
    struct sembuf consume[2];
    consume[0].sem_num = 0;
    consume[0].sem_op = -1;
    consume[0].sem_flg = SEM_UNDO;
    consume[1].sem_num = 1;
    consume[1].sem_op = 1;
    consume[1].sem_flg = SEM_UNDO;

    if (0 == fork()) {
        //consumer
        while (1) {
            if (semctl(semid, 0, GETVAL)) {
            sleep(1);
            printf("before consume, 0:%d, 1:%d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
            semop(semid, consume, 2);
            printf("after consume, 0:%d, 1:%d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));

            }
        }
    }
    else {
        //producer
        while (1) {
            if (semctl(semid, 1, GETVAL)) {
            sleep(2);
            unsigned short ret[2];
            semctl(semid, 0, GETALL, ret);
            printf("before produce, 0:%d, 1:%d\n", ret[0], ret[1]);
            semop(semid, produce, 2);
            semctl(semid, 0, GETALL, ret);
            printf("after produce, 0:%d, 1:%d\n", ret[0], ret[1]);

            }
        }
    }

    semctl(semid, 0, IPC_RMID);
    return 0;
}

