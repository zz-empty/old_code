#include <func.h>

int main() 
{
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

