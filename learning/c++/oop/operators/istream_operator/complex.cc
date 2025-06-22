#include "complex.h"
#include <iostream>
#include <limits>


using std::cout;
using std::endl;

Complex::Complex(double real, double image)
: _dreal(real), _dimage(image)
{
   cout << "Complex(double = 0, double = 0)" << endl; 
}

Complex::~Complex()
{
    cout << "~Complex()" << endl;
}

double Complex::getReal() const
{
    return _dreal;
}
double Complex::getImage() const
{
    return _dimage;
}

void Complex::print()
{
    if (0 == _dimage && 0 == _dreal) {
        cout << 0 << endl;
    }
    else if (0 == _dreal) {
        cout << _dimage << "i" << endl;
    }
    else {
        cout << _dreal;

        if (0 < _dimage) {
            if (1 == _dimage) {
                cout << "i" << endl;
            }
            else {
                cout << " + " << _dimage << "i" << endl;
            }
        }
        else if (0 > _dimage) {
            cout << " - " << (-1 * _dimage) << "i" << endl;
        }
        else {
            cout << endl;
        }
    }
}


#ifdef ORDINARY
//运算符重载之普通函数形式
Complex operator+(const Complex &lhs, const Complex &rhs)
{
    cout << "Complex operator+(const Complex&, const Complex&)" << endl;
    return Complex(lhs.getReal() + rhs.getReal(),
                   lhs.getImage() + rhs.getImage());
}
#endif

#ifdef MEMBER
Complex & Complex::operator+=(const Complex &rhs)
{
    cout << "Complex &operator+=(const Complex&)" << endl;
    _dreal += rhs.getReal();
    _dimage += rhs.getImage();
    return *this;
}
Complex &Complex::operator++()
{
    cout << "Complex &operator++()" << endl;
    ++_dreal;
    ++_dimage;
    return *this;
}
Complex Complex::operator++(int)
{
    cout << "Complex &operator++(int)" << endl;
    Complex tmp(*this);
    _dreal++;
    _dimage++;
    return tmp;
}
#endif

#ifdef FRIEND
Complex operator+(const Complex &lhs, const Complex &rhs)
{
    cout << "friend Complex operator+(const Complex&, const Complex&)" << endl;
    return Complex(lhs._dreal + rhs._dreal, lhs._dimage + rhs._dimage);
}

std::ostream & operator<<(std::ostream &os, const Complex &rhs)
{
    if (0 == rhs._dimage && 0 == rhs._dreal) {
        cout << 0 << endl;
    }
    else if (0 == rhs._dreal) {
        cout << rhs._dimage << "i" << endl;
    }
    else {
        cout << rhs._dreal;
        if (0 < rhs._dimage) {
            if (1 == rhs._dimage) {
                cout << "i" << endl;
            }
            else {
                cout << " + " << rhs._dimage << "i" << endl;
            }
        }
        else if (0 > rhs._dimage) {
            cout << " - " << (-1 * rhs._dimage) << "i" << endl;
        }
        else {
            cout << endl;
        }
    }
    return os;
}

std::istream & operator>>(std::istream &is, Complex &rhs)
{
    /* std::cin >> rhs._dreal >> rhs._dimage; */
    readDoubel(is, rhs._dreal);
    readDoubel(is, rhs._dimage);
    return is;
}
#endif


void readDoubel(std::istream &is, double &number)
{
    while (is >> number, !is.eof()) {
        if (is.bad()) {
            std::cerr << "The istream is bad" << endl;
            return;
        }

        else if (is.fail()) {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "---please input a double data---" << endl;
        }

        else {
            cout << "number = " << number << endl;
            break;
        }
    }
}
