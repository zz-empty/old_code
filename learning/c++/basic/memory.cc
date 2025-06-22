#include <iostream>

using std::cout;
using std::endl;

int a;
int *p1;

int main()
{
    int b;
    int *p2 = static_cast<int*>(malloc(sizeof(int)));
    char *pstr = "hello";
    static int si = 10;

    printf("&a = %p\n", &a);//全局区
    printf("&p1 = %p\n", &p1);
    printf("p1 = %p\n", p1);

    printf("&b = %p\n", &b);//栈区
    printf("&p2 = %p\n", &p2);

    printf("p2 = %p\n", p2);//堆区

    printf("\"hello\" = %p\n", &"hello");//文字常量区

    printf("main = %p\n", main);//程序代码区
    printf("&main = %p\n", &main);

    printf("&si = %p\n", &si);//静态区

    return 0;
}

