#include "Pimpl.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{


class Line::PointPimpl
{
public:
    PointPimpl(int x1, int y1, int x2, int y2);
    ~PointPimpl();
    void printPoint();
private:
    class Point
    {
    public:
        Point(int ix, int iy)
        :_ix(ix)
        ,_iy(iy)
        {}

        ~Point()
        {}

        void print() const
        {
            cout << "(" << _ix << "," << _iy << ")" << endl;
        }
    private:
        int _ix;
        int _iy;
    };
    
    Point _ip1;
    Point _ip2;
};

Line::PointPimpl::PointPimpl(int x1, int y1, int x2, int y2)
:_ip1(x1, y1)
,_ip2(x2, y2)
{
    cout << "PointPimpl(int, int, int, int)" << endl;
}

Line::PointPimpl::~PointPimpl()
{
    cout << "~PointPimpl()" << endl;
}

void Line::PointPimpl::printPoint()
{
   _ip1.print(); 
   _ip2.print();
}


Line::Line(int x1, int y1, int x2, int y2)
:_ppl(new PointPimpl(x1, y1, x2, y2))
{
    cout << "Line(int, int, int, int)" << endl;
}
Line::~Line()
{
    cout << "~Line()" << endl;
    if (_ppl) {
        delete _ppl;
        _ppl = nullptr;
    }
}
void Line::printLine()
{
    _ppl->printPoint();
}

}//end of namespace wd
