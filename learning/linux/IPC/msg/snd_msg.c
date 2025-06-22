#include <func.h>
typedef struct {
    long mtype;
    char mtext[256];
}MyMsg_t;

int main() 
{
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");

    MyMsg_t msg;
    msg.mtype = 1;
    memset(msg.mtext, 0, sizeof(msg.mtext));
    strcpy(msg.mtext, "hello");

    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
    return 0;
}

