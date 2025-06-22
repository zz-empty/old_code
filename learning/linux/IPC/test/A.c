#include <func.h>
int semid;
int shmid;
int *proc;
void quit(int signum)
{
    semctl(semid,0,IPC_RMID);
    shmctl(shmid,IPC_RMID,NULL);
    kill(proc[1],SIGINT);
    kill(proc[2],SIGINT);
    kill(proc[3],SIGINT);
    shmdt(proc);
    exit(0);
}
int main(int argc,char* argv[])
{
    semid = semget(1000,1,IPC_CREAT|0600);
    semctl(semid,0,SETVAL,1);
    struct sembuf P;
    P.sem_op = -1;
    P.sem_num = 0;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_op = 1;
    V.sem_num = 0;
    V.sem_flg = SEM_UNDO;
    

    shmid = shmget(1000,4096,IPC_CREAT | 0600);
    char *p = (char*)shmat(shmid,NULL,0);
    char* msg = p + 20;
    proc =  (int*)p;
    proc[0] = getpid();
    int fdr = open(argv[1],O_RDONLY);
    int fdw = open(argv[2],O_WRONLY);
    fd_set rdset;
    char buf[1024];
    proc[4] = 0;

    signal(SIGINT,quit);
    while(1)
    {
        memset(buf,0,sizeof(buf));
        FD_ZERO(&rdset);
        FD_SET(fdr,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        select(fdr + 1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(fdr,&rdset))
        {
            int ret = read(fdr,buf,sizeof(buf));
            if(ret)
            {
                semop(semid,&P,1);
                sprintf(msg,"%s",buf);
                proc[4] = 1;
                semop(semid,&V,1);
            }
            else
            {
                break;
            }
        }
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            int ret = read(STDIN_FILENO,buf,sizeof(buf));
            if(ret != 0) 
            {
                write(fdw,buf,ret);
            }
            else
            {
                write(fdw,"I'm quit!\n",10);
                break;
            }
        }
    }
    exit(0);
}
