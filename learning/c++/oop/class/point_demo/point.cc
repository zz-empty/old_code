#include "point.h"
#include <iostream>

using std::cout;
using std::endl;

Point::Point()
: _ix(0)
, _iy(0)
{

}

Point::Point(int ix, int iy)
: _ix(ix)
, _iy(iy)
{
    cout << "Point(int,int)" << endl;
}

Point::~Point()
{
    cout << "~Point()" << endl;
}

Point::Point(const Point &rhs)
: _ix(rhs._ix)
, _iy(rhs._iy)
{
    cout << "Point(const Point &)" << endl;
}

void Point::print()
{
    cout << "(" << _ix << ", " << _iy << ")" << endl;
}
