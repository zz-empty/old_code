#include <stdio.h>
#include <string.h>

#define MAX_WORD 128
#define MAX_LINE 1028

//记录单词和出现频率
typedef struct Word {
    char _wordname[MAX_WORD];
    int _wordcount;
}Word_t, *pWord_t;

//从字符串中剥离出一个个单词
int word_from_line(char *line) {
    int len = strlen(line);
    int state = 0;//是否处于单词中

    int nw = 0; //单词数
    char word[MAX_WORD] = "";
    int word_start = 0;
    
    for (int i = 0; i < len; i++) {
        if (line[i] < 'A' || (line[i] > 'Z' && line[i] < 'a') || line[i] > 'z') {
            state = 0;
            if (0 != word_start) {
                //表示已经扫描到了一个单词
                strncpy(word, &line[i] - word_start, word_start);
                word_start = 0;
                puts(word); //显示单词
                memset(word, 0, MAX_WORD);  //清空单词缓冲区
            }
        } else {
            if (0 == state) {
                state = 1;
                ++nw;
            }
            word_start++;   //记录单词的长度
        }
    }

    return nw;
}

int main()
{
    //读入一个字符串
    char str[MAX_LINE] = "";
    printf("please input a str: ");
    fgets(str, MAX_LINE, stdin);

    //将字符串拆分
    word_from_line(str);
    return 0;
}

