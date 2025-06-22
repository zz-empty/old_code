#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_w");
    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_r");
    puts("chat2 connected!");

    char buf[1024] = {0};
    int ret;
    fd_set rdset;
    struct timeval timeout;//set overtime
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(fdr, &rdset);
        FD_SET(STDIN_FILENO, &rdset);
        timeout.tv_sec = 5;
        timeout.tv_usec = 500000;
        ret = select(fdr+1, &rdset, NULL, NULL, &timeout);
        ERROR_CHECK(ret, -1, "select");
        if (ret != 0) {
            if (FD_ISSET(fdr, &rdset)) {
                printf("\nmsg from pipe");
                // 获取消息时间
                time_t rawtime;  
                struct tm * timeinfo;  
                ret = read(fdr, &rawtime, sizeof(rawtime));
                if (0 == ret) {
                    //chat end
                    puts("chat ended!");
                    break;
                }
                timeinfo = localtime(&rawtime);  
                // 定义时间格式字符串  
                char buffer[80];  
                strftime(buffer, 80, "%Y-%m-%d %H:%M", timeinfo);  
                // 打印格式化后的时间  
                printf("当前时间是: %s\n", buffer);  
                memset(buf, 0, sizeof(buf));
                ret = read(fdr, buf, sizeof(buf));
                if (0 == ret) {
                    puts("chat end");
                    break;
                }
                puts(buf);
            }
            else if (FD_ISSET(STDIN_FILENO, &rdset)) {
                puts("msg from stdin");
                memset(buf, 0, sizeof(buf));
                ret = read(0, buf, sizeof(buf));
                if (0 == ret) {
                    write(fdw, "Good luck", 9);
                    puts("I quit");
                    close(fdw);
                    break;
                }

                time_t nowtime;  
                time(&nowtime);  
                write(fdw, &nowtime, sizeof(nowtime));

                write(fdw, buf, strlen(buf));
            }
        }
        else {
            printf("time out!\n");
        }

    }

    close(fdr);
    close(fdw);
    return 0;
}

