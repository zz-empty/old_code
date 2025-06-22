#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class Complex
{
    friend class Point;
public:
    Complex(float dreal, float dimage)
    :_dreal(dreal), _dimage(dimage)
    {
    }
    friend ostream &operator<<(ostream &os, const Complex &rhs);
private:
    float _dreal;
    float _dimage;
};

ostream &operator<<(ostream &os, const Complex &rhs)
{
    cout << rhs._dreal << " + " << rhs._dimage << "i" << endl;
    return os;
}

class Point
{
public:
    Point(int ix = 0, int iy = 0);
    ~Point();
    Point(double d);
    Point(const Complex &rhs);
    friend ostream &operator<<(ostream &os, const Point &rhs);
private:
    int _ix;
    int _iy;
};

ostream &operator<<(ostream &os, const Point &rhs)
{
    cout << "(" << rhs._ix << ", " << rhs._iy << ")";
    return os;
}

Point::~Point()
{
    cout << "~Point()" << endl;
}

Point::Point(int ix, int iy)
:_ix(ix),_iy(iy)
{
    cout << "Point(int, int)" << endl;
}

Point::Point(double d)
:_ix(static_cast<int>(d))
, _iy(_ix)
{
}

Point::Point(const Complex &rhs)
:_ix(rhs._dreal)
,_iy(rhs._dimage)
{
}

int main()
{
    Point p1(3, 5);
    cout << "p1 = " << p1 << endl;

    cout << endl;
    Point p2 = 5;
    cout << "p2 = " << p2 << endl;

    cout << endl;
    double d = 10;
    Point p3 = d;
    cout << "p3 = " << p3 << endl;

    cout << endl;
    Point p4 = Complex(5, 8);
    cout << "p4 = " << p4 << endl;

    return 0;
}

