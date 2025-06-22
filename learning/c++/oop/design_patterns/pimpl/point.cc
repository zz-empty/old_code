#include "point.h"
#include <iostream>

using std::cout;
using std::endl;



class Line::PointPimpl
{
public:
    PointPimpl(int x1, int y1, int x2, int y2)
    :_pt1(x1, y1)
    ,_pt2(x2, y2)
    {
        cout << "PointPimpl(int, int, int, int)" << endl;
    }
    ~PointPimpl()
    {
        cout << "~PointPimpl()" << endl;
    }
    void printPimpl()
    {
        _pt1.print();
        _pt2.print();
    }
private:
    class Point
    {
    public:
        Point(int ix = 0, int iy = 0)
        :_ix(ix)
        ,_iy(iy)
        {
            cout << "Point(int = 0, int = 0)" << endl;
        }
        ~Point()
        {
            cout << "~Point()" << endl;
        }
        void print() const
        {
            cout << "(" << _ix << "," << _iy << ")" << endl;
        }
    private:
        int _ix;
        int _iy;
    };
private:
    Point _pt1;
    Point _pt2;
};

Line::Line(int x1, int y1, int x2, int y2)
:_pimpl(new PointPimpl(x1, y1, x2, y2))
{
    cout << "Line(int, int, int, int)" << endl;
}
void Line::printLine()
{
    _pimpl->printPimpl();
}
Line::~Line()
{
    cout << "~Line()" << endl;
    if (_pimpl) {
        delete _pimpl;
        _pimpl = nullptr;
    }
}
