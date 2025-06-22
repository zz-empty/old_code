#include <stdio.h>
#include <string.h>

void str_erase(char *str, char c)
{
    if (0 == strlen(str)) {
        printf("string is empty!\n");
        return;
    }

    size_t offset = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (c == str[i]) {
            ++offset;
        }
        else {
            str[i - offset] = str[i];
        }
    }

    str[strlen(str) - offset] = '\0';
    return;
}
