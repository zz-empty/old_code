#include "qq.h"
typedef struct {
    long mtype;
    char mtext[128];
}MyMsg_t;

int main() 
{
    printf("pid = %d\n", getpid());
    pids[2] = getpid();
    printf("pids[2] = %d\n", pids[2]);
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");
    MyMsg_t msg;

    while(1) {
        memset(&msg, 0, sizeof(msg));
        int ret = msgrcv(msgid, &msg, sizeof(msg.mtext), 0, 0);        
        if (2 == msg.mtype) {
            puts(msg.mtext);
            break;
        }
        if (ret > 0)  {
            puts(msg.mtext);
        }
    }
    return 0;
}

