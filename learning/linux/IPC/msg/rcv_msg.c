#include <func.h>
typedef struct{
    long mtype;
    char mtext[256];
}MyMsg_t;

int main() 
{
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");

    MyMsg_t msg;
    memset(&msg, 0, sizeof(msg));
    msgrcv(msgid, &msg, sizeof(msg.mtext), 0, 0);
    printf("typed = %ld, msg = %s\n", msg.mtype, msg.mtext);
    return 0;
}

