#include <func.h>

int check_endian() {
    unsigned int num = 0x12345678;
    char *c = (char*)&num;
    if (*c == 0x78) {
        return 1; //Little-Endian
    }
    else {
        return 0;//Big-Endian
    }
}

int main() 
{
    if (check_endian()) {
        printf("The computer is Little-Endian!\n");
    }
    else {
        printf("The computer is Big-Endian!\n");
    }
    return 0;
}

