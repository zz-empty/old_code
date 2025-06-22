#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point();
    Point(int ix, int iy);
    ~Point();
    Point(const Point &rhs);

    void print();
private:
    int _ix;
    int _iy;
};

#endif
