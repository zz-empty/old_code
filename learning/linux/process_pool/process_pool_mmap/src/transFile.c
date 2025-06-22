#include "../include/process_pool.h"

/* void sigFunc(int sigNum) { */
/*     printf("sig_%d is comming!\n", sigNum); */
/* } */

int transFile(int clientFd)
{
    /* signal(SIGPIPE, sigFunc); */

    //send data according to protocol, resolve tcp sticking
    Train_t train;
    memset(&train, 0, sizeof(Train_t));

    int fd = open("file", O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    /* int ret; */

    //send filename to client
    train.data_len = 4;
    memcpy(train.buf, "file", 4);
    send(clientFd, &train, sizeof(int) + train.data_len, 0);

    //get filesize by fd
    struct stat fileInfo;
    bzero(&fileInfo, sizeof(fileInfo));
    fstat(fd, &fileInfo);
    //send filesize to client
    train.data_len = sizeof(fileInfo.st_size);
    memcpy(train.buf, &fileInfo.st_size, train.data_len);
    send(clientFd, &train, sizeof(train.data_len) + train.data_len, 0);
    printf("filesize = %ld\n", fileInfo.st_size);


    //send file to client
    char *pMap = (char*)mmap(NULL, fileInfo.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(pMap, (char*)-1, "mmap");

    send(clientFd, pMap, fileInfo.st_size, 0);
    munmap(pMap, fileInfo.st_size);

    return 0;
}
