#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    virtual void a()
    {
        cout << "A::a()" << endl;
    }
    virtual void b()
    {
        cout << "A::b()" << endl;
    }
    virtual void c()
    {
        cout << "A::c()" << endl;
    }
};

class B
{
public:
    virtual 
    void a()
    {
        cout << "B::a()" << endl;
    }
    virtual 
    void b()
    {
        cout << "B::b()" << endl;
    }
    void c()
    {
        cout << "B::c()" << endl;
    }
    void d()
    {
        cout << "B::d()" << endl;
    }
};

class C
:public A
,public B
{
public:
    virtual 
    void a()
    {
        cout << "C::a()" << endl;
    }
    void c()
    {
        cout << "C::c()" << endl;
    }
    void d()
    {
        cout << "C::d()" << endl;
    }
};

class D
:public C
{
public:
    void c() override
    {
        cout << "D::c()" << endl;
    }
};

void test()
{
    C c;

    cout << endl;
    A &pa = c;
    pa.a(); //C::a
    pa.b(); //A::b
    pa.c(); //C::c

    cout << endl;
    B *pb = &c;
    pb->a();    //C::a
    pb->b();    //B::b
    pb->c();    //C::c
    pb->d();    //C::d

    cout << endl;
    C *pc = &c;
    pc->a();    //C::a
    pc->A::b(); //A::b
    pc->B::b(); //B::b
    pc->c();    //C::c
    pc->d();    //C::d
}

void test_d()
{
    D d;
    cout << "sizeof(D) = " << sizeof(D) << endl;
    C *pc = &d;
    pc->c();
}

int main()
{
    /* test(); */
    test_d();
    return 0;
}

