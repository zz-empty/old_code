#pragma vtordisp(off)
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
    A() : _ia(10) {}

    /*virtual*/
    void f()
    {
        cout << "A::f()" << endl;
    }
private:
    int _ia;
};

class B
: /*virtual*/ public A
{
public:
    B() : _ib(20) {}

    void fb()
    {
        cout << "A::fb()" << endl;
    }

    /*virtual*/
    void f()
    {
        cout << "B::f()" << endl;
    }

    //virtual
    void fb2()
    {
        cout << "B::fb2()" << endl;
    }

private:
    int _ib;
};

int main(void)
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    B b;
    return 0;
}
