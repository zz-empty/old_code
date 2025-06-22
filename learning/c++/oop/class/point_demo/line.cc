#include "line.h"
#include <iostream>

using std::cout;
using std::endl;


Line::Line(int x1, int y1, int x2, int y2)
/* : _pt1(x1, y1) */
/* , _pt2(x2, y2) */
{
    cout << "Line(int, int, int, int)" << endl;
}

Line::~Line()
{
    cout << "~Line()" << endl;
}

Line::Line(const Line &rhs)
{

}

void Line::print()
{
    _pt1.print();
    _pt2.print();
}
