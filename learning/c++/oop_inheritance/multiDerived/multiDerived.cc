#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }
    void print()
    {
        cout << "A::print()" << endl;
    }
    ~A()
    {
        cout << "~A()" << endl;
    }
};

class B
{
public:
    B()
    {
        cout << "B()" << endl;
    }
    void print()
    {
        cout << "B::print()" << endl;
    }
    ~B()
    {
        cout << "~B()" << endl;
    }
};

class C
{
public:
    C()
    {
        cout << "C()" << endl;
    }
    void print()
    {
        cout << "C::print()" << endl;
    }
    ~C()
    {
        cout << "~C()" << endl;
    }
};

class D
:public A
,public B
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
    D d;
    d.A::print();
    d.B::print();
    d.C::print();
    return 0;
}

