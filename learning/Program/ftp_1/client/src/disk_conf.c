#include "head.h"

//得到一行中'='符号后面的字符串
static void set_arg(char *line, char *arg)
{
    //将指针偏移到字符=
    char *ptr = strchr(line, '=');
    if (NULL == ptr) {
        fprintf(stderr, "conf_file is error!\n");
        exit(-1);
    }

    //= 后面的字符串
    strcpy(arg, ptr + 2);
}

//从配置文件中获取参数
void conf_get(char *conf, char *ip, char *port)
{
    FILE *fp = fopen(conf, "r");
    EXIT_CHECK(fp, NULL, "fopen");
    char line[128] = "";

    //得到ip
    fgets(line, sizeof(line), fp);
    line[strlen(line) - 1] = '\0';
    set_arg(line, ip);

    //得到port
    memset(line, 0, sizeof(line));
    fgets(line, sizeof(line), fp);
    line[strlen(line) - 1] = '\0';
    set_arg(line, port);

    fclose(fp);
}
