#include "../include/process_pool.h"

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

    //recv data
    memset(buf, 0, sizeof(buf));
    recv(sfd, &data_len, sizeof(int), 0);
    recv(sfd, buf, data_len, 0);
    //write data to file
    write(fd, buf, data_len);

    printf("recv finish!\n");

    close(sfd);
    return 0;
}
