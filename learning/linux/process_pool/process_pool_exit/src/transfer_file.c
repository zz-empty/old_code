/* #define _GNU_SOURCE */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//send
#include <sys/socket.h>
#include <sys/sendfile.h>


#define ERROR_CHECK(ret, num, msg) { if (ret == num) {\
    perror(msg); return -1;} }


typedef struct {
    int data_len;
    char buf[1000];
}Train_t, *pTrain_t;

int send_file(int clientFd, char *filename)
{

    //send data according to protocol, resolve tcp sticking
    Train_t train;
    memset(&train, 0, sizeof(Train_t));

    //将文件名扩展为文件路径
    char filepath[128] = {0};
    sprintf(filepath, "../resource/%s", filename);

    //根据文件路径打开传输文件
    int file_fd = open(filepath, O_RDONLY);
    ERROR_CHECK(file_fd, -1, "open");


    int fd = open(filepath, O_RDWR);
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
#if 0
    int transFds[2];
    pipe(transFds);
    int recvLen = 0;

    while (recvLen < fileInfo.st_size) {
        ret = splice(fd, 0, transFds[1], 0, fileInfo.st_size, 0);
        ret = splice(transFds[0], 0, clientFd, 0, ret, 0);
        recvLen += ret;
    }
#else
    sendfile(clientFd, fd, 0, fileInfo.st_size);

    /* char *pMap = (char*)mmap(NULL, fileInfo.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); */
    /* ERROR_CHECK(pMap, (char*)-1, "mmap"); */
    /* send(clientFd, pMap, fileInfo.st_size, 0); */
    /* munmap(pMap, fileInfo.st_size); */
#endif
    close(fd);

    return 0;
}
