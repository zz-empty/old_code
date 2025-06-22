#include <stdio.h>

#define MAX_WORD 128
#define MAX_LINE 1028

//打印单词的水平直方图
void show_word_chart_level(char *word) {
    char model[] = "**";
    while (*word != '\0') {
        puts(model);
        word++;
    }
}

int main()
{
    //读入一个字符串
    char str[MAX_LINE] = "";
    printf("please input a str: ");
    /* fgets(str, MAX_LINE, stdin); */
    scanf("%s", str);

    show_word_chart_level(str);


    return 0;
}

