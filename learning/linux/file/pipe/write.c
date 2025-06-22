#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    int fdw = open(argv[1], O_WRONLY);//1.pipe write
    ERROR_CHECK(fdw, -1, "open_w");
    int fdr = open(argv[2], O_RDONLY);//2.pipe read
    ERROR_CHECK(fdr, -1, "open_r");
    puts("write OK");

    char buf[1024] = {0};
    int ret;
    while(1) {
        //write to pipe
        fgets(buf, sizeof(buf), stdin);
        write(fdw, buf, strlen(buf));

        //read from pipe
        ret = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "read");
        if (0 == ret) {
            break;
        }
        puts(buf);

    }

    close(fdw);
    close(fdr);
    return 0;
}

