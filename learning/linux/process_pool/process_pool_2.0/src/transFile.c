#include "../include/process_pool.h"

typedef struct {
    int data_len;
    char buf[1000];
}Train_t, *pTrain_t;

int transFile(int pipeFd)
{
    Train_t train;
    memset(&train, 0, sizeof(Train_t));

    int fd = open("file", O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    int ret;

    //send filename
    train.data_len = 4;
    memcpy(train.buf, "file", 4);
    send(pipeFd, &train, sizeof(int) + train.data_len, 0);

    //send file
    memset(train.buf, 0, sizeof(train.buf));
    ret = read(fd, train.buf, sizeof(train.buf));
    train.data_len = ret;
    send(pipeFd, &train, sizeof(int) + train.data_len, 0);

    return 0;
}
