#ifndef __COMPLEX_H__
#define __COMPLEX_H__

/* #define ORDINARY */
#define MEMBER
#define FRIEND

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
#endif

#ifdef FRIEND
    friend Complex operator+(const Complex &lhs, const Complex &rhs);
#endif
private:
    double _dreal;
    double _dimage;
};

#ifdef ORDINARY
Complex operator+(const Complex &lhs, const Complex &rhs);
#endif

#endif
