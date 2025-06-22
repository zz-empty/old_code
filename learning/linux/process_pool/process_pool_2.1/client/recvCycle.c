#include <func.h>

int recvCycle(int sockFd, void *buf, int totalLen)
{
    int ret = 0;
    int recvLen = 0;
    while (recvLen < totalLen) {
        //avoid recover buf
        ret = recv(sockFd, (char*)buf + recvLen, totalLen - recvLen, 0);
        if (0 == ret) {
            printf("server break!\n");
            return -1;
        }

        recvLen += ret;
    }

    return recvLen;
}
