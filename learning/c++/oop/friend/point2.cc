#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

//声明
class Point;

class Line
{
public:
    float distance(const Point &lhs, const Point &rhs);
};

class Point
{
public:
    Point(int ix = 0, int iy = 0);
    ~Point();

    void print();
    friend float Line::distance(const Point &lhs, const Point &rhs);

private:
    float _ix;
    float _iy;
};

//实现
Point::~Point()
{
    cout << "~Point()" << endl;
}

Point::Point(int ix, int iy)
:_ix(ix),_iy(iy)
{
    cout << "Point(int = 0, int = 0)" << endl;
}

void Point::print()
{
    cout << "Point = (" << _ix << "," << _iy << ")" << endl;
}

float Line::distance(const Point &lhs, const Point &rhs)
{
    return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy);
}

void test_friend();
int main()
{
    test_friend();
    return 0;
}

void test_friend()
{
    Point p1(1,3);
    p1.print();

    Point p2(4,7);
    p2.print();

    cout << "两点的距离：" << Line().distance(p1, p2) << endl;
}
