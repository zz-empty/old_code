#include "complex.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

//运算符+=，推荐使用成员函数重载，因为对象本身发生
void test_plus_equal();
//运算符++，推荐使用成员函数重载
void test_increase();
void test_ostream();
void test_istream();


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

void test_increase()
{
    Complex c1(2, 3);
    c1.print();

    cout << endl;
    (++c1).print();

    cout << endl;
    (c1++).print();

    cout << endl;
    Complex c3(-1, 0);
    c3.print();
}

void test_ostream()
{
    Complex c1(3, 4);

    Complex c2(0, 1);
    cout << "c1 = " << c1 << endl << "c2 = " << c2 << endl;
}
void test_istream()
{
    Complex c;
    cin >> c;
    cout << "c = " << c << endl;

}

int main()
{
    /* test_plus_equal(); */
    /* test_increase(); */

    /* test_ostream(); */
    test_istream();
    return 0;
}

