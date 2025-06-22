# ifndef __POINT_H__
# define __POINT_H__

#include <iostream>
using namespace std;

class Point
{
public:
    Point(const double x, const double y)
        :_x(x)
         ,_y(y)
    {}
    void print()
    {
        cout << "(x,y) = " << "(" << _x << "," << _y << ")" << endl;
    }
    ~Point() = default;
private:
    double _x;
    double _y;
};

# endif
