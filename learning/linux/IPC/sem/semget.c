#include <func.h>

int main() 
{
    int semid = semget(1000, 1, IPC_CREAT|0600);
    printf("semid = %d\n", semid);
    return 0;
}

