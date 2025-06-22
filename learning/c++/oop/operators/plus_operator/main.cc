#include "complex.h"
#include <iostream>

using std::cout;
using std::endl;

//运算符+，推荐使用友元函数形式重载，因为保证操作数是两个
void test_plus();

void test_plus()
{
    Complex c1(3, 4);
    cout << "c1 = ";
    c1.print();

    cout << endl;
    Complex c2(8, 3);
    cout << "c2 = ";
    c2.print();

    cout << endl << endl;
    Complex c3 = c1 + c2;
    cout << "c3 = ";
    c3.print();
}

int main()
{
    test_plus();
    return 0;
}

