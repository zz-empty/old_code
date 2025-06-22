#include <stdio.h>
#include <string.h>

#define MAX_LINE 1028

//统计一个字符串中有多少个单词
int wordCount(char *line) {
    int len = strlen(line);
    int state = 0;//是否处于单词中

    int nw = 0; //单词数
    
    for (int i = 0; i < len; i++) {
        if (line[i] < 'A' || (line[i] > 'Z' && line[i] < 'a') || line[i] > 'z') {
            state = 0;
        } else if (0 == state) {
            state = 1;
            ++nw;
        }
    }

    return nw;
}

int main(int argc, char **argv)
{
    /* char str[MAX_LINE] = ""; */
    /* printf("please input a str: "); */
    /* fgets(str, MAX_LINE, stdin); */

    if (2 != argc) {
        fprintf(stderr, "args error!\n");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (NULL == fp) {
        perror("file open failed!");
        return -1;
    }

    //统计文件中的字符数，行数，单词数
    int nc = 0;
    int nl = 0;
    int nw = 0;

    char line[MAX_LINE] = "";
    while (fgets(line, MAX_LINE, fp)) {
        nc += strlen(line);
        nl++;
        nw += wordCount(line);
    }

    printf("nc = %d, nl = %d, nw = %d\n", nc, nl, nw);

    fclose(fp);
    return 0;
}

