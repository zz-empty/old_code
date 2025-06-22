#include <func.h>

int main() 
{
    //create sem
    int semid = semget(1000, 2, IPC_CREAT|0600);
    ERROR_CHECK(semid, -1, "semget");
    //init sem
    unsigned short arr[2] = {3, 5};
    int ret = semctl(semid, 0, SETALL, arr);
    ERROR_CHECK(ret, -1, "semctl");

    //get semval
    unsigned short val[2];
    semctl(semid, 0, GETALL, val);
    for (int i = 0; i < 2; ++i) {
        printf("retval[%d] = %d\n", i, val[i]);
    }

    return 0;
}

