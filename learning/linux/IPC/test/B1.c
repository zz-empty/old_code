#include <func.h>
typedef struct
{
    long msgtype;
    char text[1024];
}msg_t;
int main()
{
    int msgid = msgget(1000,IPC_CREAT | 0600);
    msg_t mymsg;
    int shmid = shmget(1000,4096,IPC_CREAT|0600);
    char* p = (char*)shmat(shmid,NULL,0);
    int* proc = (int*)p;
    proc[3] = getpid();
    while(1)
    {
        int ret = msgrcv(msgid,mymsg.text,sizeof(mymsg.text),0,IPC_NOWAIT);
        if(ret >= 0)
        {
            printf("%s",mymsg.text);
        }
    }

}
