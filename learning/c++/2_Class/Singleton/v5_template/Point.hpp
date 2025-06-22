#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int ix, int iy)
    :_ix(ix)
    ,_iy(iy)
    {}

    Point(const Point &rhs)
    :_ix(rhs._ix)
    ,_iy(rhs._iy)
    {}

    Point() = default;
    ~Point() = default;

    void print()
    {
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }
private:
    int _ix;
    int _iy;
};

#endif
