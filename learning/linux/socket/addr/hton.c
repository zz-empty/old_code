#include <func.h>

int main() 
{
    short port = 0x1234;
    short nport = htons(port);
    printf("nport = %x\n", nport);
    printf("port = %x\n", ntohs(nport));
    return 0;
}

