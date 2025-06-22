#include "complex.h"
#include <iostream>

using std::cout;
using std::endl;

//运算符+=，推荐使用成员函数重载，因为对象本身发生
void test_plus_equal();

void test_plus_equal()
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

    cout << endl << endl;
    c1 += c2;
    cout << "c1 = ";
    c1.print();
}

int main()
{
    test_plus_equal();
    return 0;
}

