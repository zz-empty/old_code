#ifndef __LINE_H__
#define __LINE_H__

#include "point.h"
#include <iostream>

using std::cout;
using std::endl;

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    Line(const Line &rhs);

    void print();

private:
    Point _pt1;
    Point _pt2;
};

#endif
