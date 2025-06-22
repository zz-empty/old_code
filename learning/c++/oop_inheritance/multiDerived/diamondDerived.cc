#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    A(double x = 0)
    :_dx(x)
    {
        cout << "A(double)" << endl;
    }
    void setX(double x)
    {
        _dx = x;
    }
    void print() const
    {
        cout << "A::_dx = " << _dx << endl;
    }
    ~A()
    {
        cout << "~A()" << endl;
    }
private:
    double _dx;
};

class B
:virtual public A
{
public:
    B()
    :A(10)
    {
        cout << "B()" << endl;
    }
};

class C
:virtual public A
{
public:
    C()
    :A(30)
    {
        cout << "C()" << endl;
    }
};

class D
:public B
,public C
{
public:
    D()
    {
        cout << "D()" << endl;
    }
    ~D()
    {
        cout << "~D()" << endl;
    }
};

int main()
{
    cout << "sizeof(A) = " << sizeof(A) << endl;
    cout << "sizeof(B) = " << sizeof(B) << endl;
    cout << "sizeof(C) = " << sizeof(C) << endl;
    cout << "sizeof(D) = " << sizeof(D) << endl;

    cout << endl;
    D d;
    d.B::print();
    d.C::print();

    cout << endl;
    d.B::setX(90);
    d.B::print();
    d.C::print();

    cout << endl;
    d.setX(200);
    d.print();
    return 0;
}

