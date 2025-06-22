#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_r");
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_w");
    puts("chat1 connected!");

    char buf[1024] = {0};
    int ret;
    fd_set rdset;//listen readset
    struct timeval timeout;//set overtime
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(fdr, &rdset);
        FD_SET(STDIN_FILENO, &rdset);
        timeout.tv_sec = 5;
        timeout.tv_usec = 500000;
        ret = select(fdr+1, &rdset, NULL, NULL, &timeout);
        ERROR_CHECK(ret, -1, "select");
        if (0 == ret) {
            puts("time out!");
        }
        else {
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

                //print msg
                memset(buf, 0, sizeof(buf));
                ret = read(fdr, buf, sizeof(buf));
                if (0 == ret) {
                    //chat end
                    puts("chat ended!");
                    break;
                }
                puts(buf);
            }
            if (FD_ISSET(STDIN_FILENO, &rdset)) {
                memset(buf, 0, sizeof(buf));
                int ret = read(STDIN_FILENO, buf, sizeof(buf));
                if (0 == ret) {
                    //exit chat
                    puts("quit!");
                    write(fdw, "you are a nice man!Bye!", 19);
                    break;
                }
                // 获取当前时间的原始秒数  
                time_t nowtime;  
                time(&nowtime);  
                write(fdw, &nowtime, sizeof(nowtime));

                //send msg
                write(fdw, buf, strlen(buf));
            }
        }
    }

    close(fdr);
    close(fdw);
    return 0;
}

