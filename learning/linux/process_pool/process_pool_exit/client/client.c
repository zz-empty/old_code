#include <func.h>
int recvCycle(int sockFd, void *buf, int totalLen);

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 3);
    char *ip = argv[1];
    char *port = argv[2];

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");

    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(atoi(port));

    int ret = 0;
    ret = connect(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "connect");

    printf("connect server!\n");

    int data_len = 0;
    char buf[1000] = {0};

    //recv filename
    recv(sfd, &data_len, sizeof(int), 0);
    recv(sfd, buf, data_len, 0);
    printf("recv filename\n");
    //open file
    int fd = open(buf, O_RDWR|O_CREAT, 0600);
    printf("open file\n");

    off_t filesize = 0;
    off_t recvLen = 0;
    //receive filesize from sfd
    recv(sfd, &data_len, sizeof(int), 0);
    recv(sfd, &filesize, data_len, 0);
    printf("filesize = %ld\n", filesize);

    //ftruncate
    ret = ftruncate(fd, filesize);

    //set received percentage
    float rate = 0;

    //record run_time
    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin, NULL);

    //recv filedata from server
#if 1
    char *pMap = (char*)mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(pMap, (char*)-1, "mmap");

    recv(sfd, pMap, filesize, MSG_WAITALL);

    munmap(pMap, filesize);

    gettimeofday(&end, NULL);
    printf("transfer time = %ld us\n", (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec);
#else
    while (1) {
        memset(buf, 0, sizeof(buf));
        ret = recv(sfd, &data_len, sizeof(int), 0);
        if (0 == data_len) {
            //transfer finish
            printf("\n\n");
            break;
        }

        if (1000 != data_len) {
            //get last data_len
            printf("dataLen = %d\n", data_len);
        }

        /* ret = recv(sfd, buf, data_len, MSG_WAITALL); */
        ret = recvCycle(sfd, buf, data_len);

        //print percentage bar
        recvLen += ret;
        rate = (float)recvLen / filesize;
        printf("====================================================================%5.2f%%\r", rate * 100);
        fflush(stdout);

        //write data to file
        write(fd, buf, data_len);
    }
#endif
    printf("recv finish!\n");

    close(sfd);
    return 0;
}
