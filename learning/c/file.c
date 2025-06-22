#include <stdio.h>

#define FILE_CHECK(ret, num, msg) {if (ret == num) { fprintf(stderr, "%s\n", msg); return -1; }}

//读写文件

int main(int argc, char **argv)
{
    if (2 != argc) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[1]);
    }
    //创建一个文件流，以读写的方式
    FILE *fp = fopen(argv[1], "w+");
    FILE_CHECK(fp, NULL, "File failed!");

    fprintf(fp, "%d\t%s\t%5.2f\n", 1001, "xiaoming", 200.3);
    fseek(fp, 0, SEEK_SET);
    int id;
    char name[20];
    float score;
    fscanf(fp, "%d%s%f", &id, name, &score);
    printf("id:%d, name:%s, score:%5.2f\n", id, name, score);

    //读取文件内容
    /* char line[100] = ""; */
    /* while (fgets(line, sizeof(line), fp)) { */
    /*     printf("%s", line); */
    /* } */

    //写入文件内容
    /* fprintf(fp, "%d %s", 100, "is ok"); */

    //关闭一个文件流
    fclose(fp);

    return 0;
}

