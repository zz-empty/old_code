#include "../include/process_pool.h"

void sigFunc(int sigNum) {
    printf("sig_%d is comming!\n", sigNum);
}

int transFile(int clientFd)
{
    signal(SIGPIPE, sigFunc);

    //send data according to protocol, resolve tcp sticking
    Train_t train;
    memset(&train, 0, sizeof(Train_t));

    int fd = open("file", O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    int ret;

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
    while (1) {
        memset(train.buf, 0, sizeof(train.buf));
        ret = read(fd, train.buf, sizeof(train.buf));
        if (0 == ret) {
            //transfer finish
            send(clientFd, &ret, 4, 0);
            break;
        }
        train.data_len = ret;
        
        //when clientFd is disconnect, 
        //send_Func first reseive -1 and second reseive SIGPIPE, than terminate childProcess
        ret = send(clientFd, &train, sizeof(int) + train.data_len, 0);
        if (-1 == ret) {
            printf("client disconnect!\n");
            break;
        }
    }

    return 0;
}
