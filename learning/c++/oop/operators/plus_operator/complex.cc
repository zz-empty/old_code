#include "complex.h"
#include <iostream>


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
    cout << _dreal << "+" << _dimage << "i" << endl;
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
Complex Complex::operator+(const Complex &rhs)
{
    cout << "Complex operator+(const Complex&)" << endl;
    return Complex(getReal() + rhs.getReal(), getImage() + rhs.getImage());
}
#endif

#ifdef FRIEND
Complex operator+(const Complex &lhs, const Complex &rhs)
{
    cout << "friend Complex operator+(const Complex&, const Complex&)" << endl;
    return Complex(lhs._dreal + rhs._dreal, lhs._dimage + rhs._dimage);
}
#endif
