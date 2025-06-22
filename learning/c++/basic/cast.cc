#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

void test()
{
    float num = 3.14;
    int num1 = 10;

    num1 = int(num);
    /* num1 = static_cast<int>(num); */
    cout << "num1 = " << num1 << endl;
}
void test2() 
{
    void *ptr = malloc(sizeof(int));
    int *pInt = static_cast<int*>(ptr);

    free(pInt);
    pInt = NULL;
}
void test3()
{
    const int num = 10;
    int *p = const_cast<int*>(&num);
    *p += 1;
    cout << "*p = " << *p << endl;
}

int main()
{
    test3();
    return 0;
}
