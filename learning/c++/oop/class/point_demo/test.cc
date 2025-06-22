#include "point.h"
#include "line.h"
#include <iostream>

using std::cout;
using std::endl;

//拷贝构造函数的调用时机，当对象作为形参时
void func(Point pt)
{
    cout << "func()" << endl;
    pt.print();
    cout << endl;
}

//拷贝构造函数的调用时机，当对象作为函数返回值时
Point func2()
{
    cout << "func2()" << endl;
    Point pt3(33, 44);
    cout << "pt3 = ";
    pt3.print();
    return pt3;
}

void test()
{
    Point p;
    p.print();

    Point p2(2, 3);
    p2.print();

    cout << endl;
    //拷贝构造函数的调用时机，当初始化一个对象时
    /* Point p3 = p2; */
    /* p3.print(); */

    /* func(p2); */
    cout << endl;
    Point pt3 = func2();
    cout << endl;
}

void testL()
{
    Line l1(1, 2, 3, 4);
    l1.print();
}
