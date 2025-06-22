#ifndef __COMPLEX_H__
#define __COMPLEX_H__

/* #define ORDINARY */
#define MEMBER
#define FRIEND

#include <iostream>

class Complex
{
public:
    Complex(double real = 0, double image = 0);
    ~Complex();

    double getReal() const;
    double getImage() const;
    void print();

#ifdef MEMBER
    Complex &operator+=(const Complex &rhs);
    Complex &operator++();
    Complex operator++(int);
#endif

#ifdef FRIEND
    friend Complex operator+(const Complex &lhs, const Complex &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Complex &rhs);
#endif
private:
    double _dreal;
    double _dimage;
};

#ifdef ORDINARY
Complex operator+(const Complex &lhs, const Complex &rhs);
#endif

#endif
