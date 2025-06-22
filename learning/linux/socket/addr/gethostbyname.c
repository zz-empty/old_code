#include <func.h>

int main(int argc, char *argv[]) 
{
    ARGS_CHECK(argc, 2);
    struct hostent *pHost = gethostbyname(argv[1]);
    if (NULL == pHost) {
        return -1;
    }

    printf("host name: %s\n", pHost->h_name);
    for (int i = 0; pHost->h_aliases[i]; ++i) {
        printf("h_aliases = %s\n", pHost->h_aliases[i]);
    }
    printf("addrtype = %d\n", pHost->h_addrtype);
    printf("addrlen = %d\n", pHost->h_length);
    char buf[64] = {0};
    for (int i = 0; pHost->h_addr_list[i]; ++i) {
        memset(buf, 0, sizeof(buf));
        inet_ntop(pHost->h_addrtype, pHost->h_addr_list[i], buf, sizeof(buf));
        printf("ip: %s\n", buf);
    }
    return 0;
}

