#include "../include/process_pool.h"

int main(int argc, char *argv[]) 
{
    //ip port processNum
    ARGS_CHECK(argc, 4);
    //init data
    int processNum = atoi(argv[3]);
    pProcess_data_t pData = (pProcess_data_t)calloc(processNum, sizeof(process_data_t));

    //循环创建子进程
    makeChilds(processNum, pData);
    while(1);
    return 0;
}

