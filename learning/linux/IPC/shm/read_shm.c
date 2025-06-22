#include <func.h>

int main() 
{
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");
    char *p = (char*)shmat(shmid, NULL, 0);

    puts(p); 

    shmdt(p);
    return 0;
}

