#include "qq.h"

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);
    int ret;

    //A--------A1  shm
    //create shm
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");
    //connect shm
    char *p = (char*)shmat(shmid, NULL, 0);
    ERROR_CHECK(p, (void*)-1, "shmat");
    //create sem
    int semid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");
    //init sem
    ret = semctl(semid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl_set");
    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;
    printf("A1_pid = %d\n", pids[1]);

    //A--------B1 fifopipe
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_r");
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_w");
    puts("ChatA OK!");

    fd_set rdset;
    fd_set wrset;
    char buf[128] = {0};
    while(1) {
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);
        FD_SET(fdw, &wrset);
        ret = select(fdw+1, &rdset, &wrset, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (0 == ret) {
                puts("I quit!");
                write(fdw, "byebye\n", 7);
                break;
            }
            //send to B
            write(fdw, buf, ret);
        }
        else if (FD_ISSET(fdr, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(fdr, buf, sizeof(buf));
            if (0 == ret) {
                puts("chat end!");
                break;
            }
            //send to A1
            semop(semid, &P, 1);
            strncpy(p, buf, ret);
            semop(semid, &V, 1);
            /* write(STDOUT_FILENO, buf, ret); */
        }
    }

    shmdt(p);
    /* shmctl(shmid, IPC_RMID, NULL); */
    close(fdr);
    close(fdw);
    return 0;
}

