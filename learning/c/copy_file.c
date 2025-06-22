#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1028

void mergeSpace(char *line) {
    //将多个空格合并为一个
    int len = strlen(line);
    int ns = 0;
    for (int i = 1; i < len; i++) {
        if (' ' == line[i] && ' ' == line[i - 1]) {
            ++ns;
        }
        else {
            line[i - ns] = line[i];
        }
    }
    line[len - ns] = '\0';
}

void showSymbol(char *line) {
    //将制表符替换成'\t', 将回退符替换成'\b', 将反斜杠替换成'\\'
    char tmp[MAX_LINE] = "";
    int len = strlen(line);
    for (int i = 0, n = 0; i < len; i++, n++) {
        if ('\t' == line[i]) {
            strcat(tmp, "\\t");
            n++;
        } else if ('\b' == line[i]) {
            strcat(tmp, "\\b");
            n++;
        } else if ('\\' == line[i]) {
            strcat(tmp, "\\");
            n++;
        }
        tmp[n] = line[i];
    }

    strcpy(line, tmp);
}

int main(int argc, char **argv)
{
    if (3 != argc) {
        fprintf(stderr, "args error!\n");
        return -1;
    }

    //打开待复制的文件
    FILE *fp_from = fopen(argv[1], "r");
    //打开新文件
    FILE *fp_to = fopen(argv[2], "w+");

    //将从旧文件读到的每个字符都复制到新文件中
    //但需把多个空格合并成一个
    char line[MAX_LINE] = "";
    while (fgets(line, MAX_LINE, fp_from)) {
        mergeSpace(line);
        /* showSymbol(line); */
        fputs(line, fp_to);
    }

    

    fclose(fp_from);
    fclose(fp_to);
    return 0;
}

