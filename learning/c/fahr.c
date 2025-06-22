#include <stdio.h>

//华氏度与摄氏度的转化表

void printF(int upper) {
    printf("-------Fahr Table--------\n");
    /* for (int fahr = 0; fahr <= upper; fahr += 20) { */
    for (int fahr = upper; fahr >= 0; fahr -= 20) {
        printf("%3d\t%6.0f\n", fahr, 5.0 / 9 * (fahr - 32));
    }
}


void printC(int upper) {
    printf("-------Celeius Table--------\n");
    for (int celeius = 0; celeius <= upper; celeius += 10) {
        printf("%3d\t%6.0f\n", celeius, (celeius * 9.0 / 5) + 32);
    }
}

int main()
{
    printF(300);
    /* printC(100); */
    return 0;
}

