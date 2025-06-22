#include <func.h>
typedef struct 
{
    long msgtype;
    char text[1024];

}msg_t;
int msgid;
int shmid;
int* proc;
void quit(int signum)
{
    msgctl(msgid,IPC_RMID,NULL);
    shmctl(shmid,IPC_RMID,NULL);
    kill(proc[0],SIGINT);
    kill(proc[2],SIGINT);
    kill(proc[3],SIGINT);
    shmdt(proc);
    exit(0);
}
int main(int argc,char* argv[])
{
    msgid = msgget(1000,IPC_CREAT | 0600);
    msg_t mymsg;
    mymsg.msgtype = 0;

    shmid = shmget(1000,4096,IPC_CREAT | 0600);
    char *p = (char*)shmat(shmid,NULL,0);
    char* msg = p + 20;
    proc =  (int*)p;
    proc[1] = getpid();
    int fdw = open(argv[1],O_WRONLY);
    int fdr = open(argv[2],O_RDONLY);
    fd_set rdset;
    char buf[1024];

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
                sprintf(mymsg.text,"%s",buf);
                msgsnd(msgid,mymsg.text,ret,0);
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
