#include <func.h>

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 2);
    struct in_addr addr;//netip
    inet_aton(argv[1], &addr);
    printf("addr = %x\n", addr.s_addr);
    printf("addr = %s\n", inet_ntoa(addr));
    return 0;
}

