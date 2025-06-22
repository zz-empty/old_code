#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);//1.pipe read
    ERROR_CHECK(fdr, -1, "open_r");
    int fdw = open(argv[2], O_WRONLY);//2.pipe write
    ERROR_CHECK(fdw, -1, "open_w");
    puts("read OK!");

    char buf[1024] = {0};
    int ret;
    while(1) {
        //read from pipe
        memset(buf, 0, sizeof(buf));
        ret = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "read");
        if (0 == ret) {
            break;
        }
        puts(buf);

        //stdin to pipe
        read(0, buf, sizeof(buf));
        write(fdw, buf, strlen(buf));
        
    }

    close(fdr);
    close(fdw);
    return 0;
}

