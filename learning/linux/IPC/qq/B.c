#include "qq.h"
typedef struct {
    long mtype;
    char mtext[128];
}MyMsg_t;

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);
    int ret;

    //B--------B1
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");
    MyMsg_t msg;

    //B--------A
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_w");
    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_r");
    puts("ChatB OK!");

    fd_set rdset;
    fd_set wrset;
    char buf[128] = {0};
    while(1) {
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);

        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);

        FD_SET(fdw, &wrset);

        ret = select(fdr+1, &rdset, &wrset, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (0 == ret) {
                puts("I quit!");
                write(fdw, "byebye\n", 7);
                break;
            }
            //send to A
            write(fdw, buf, ret);
        }
        else if (FD_ISSET(fdr, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(fdr, buf, sizeof(buf));
            if (0 == ret) {
                memset(&msg, 0, sizeof(msg));
                msg.mtype = 2;
                strcpy(msg.mtext, "Chat end!");
                msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
                break;
            }
            //send B1
            memset(&msg, 0, sizeof(msg));
            msg.mtype = 1;
            strcpy(msg.mtext, buf);
            msgsnd(msgid, &msg, ret, 0);
            
            /* write(STDOUT_FILENO, buf, ret); */
        }
    }

    close(fdr);
    close(fdw);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

