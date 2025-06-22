#include <stdio.h>

typedef enum {
    SUN,
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SRT
}Weekday;

void reminder(Weekday day) {
    switch(day) {
    case MON: printf("周一工作!\n"); break;
    case TUE: printf("周二工作!\n"); break;
    case WED: printf("周三工作!\n"); break;
    case THU: printf("周四工作!\n"); break;
    case FRI: printf("周五快乐!\n"); break;
    case SRT: printf("周六快乐!\n"); break;
    case SUN: printf("周七快乐!\n"); break;
    }
}

int main()
{
    Weekday today = FRI;
    reminder(today);
    return 0;
}

