#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(long base = 0)
    :_base(base)
    {
        cout << "Base(long = 0)" << endl;
    }
    ~Base()
    {
        cout << "~Base()" << endl;
    }

    virtual 
    void f()
    {
        cout << "virtual void Base::f()" << endl;
    }
    virtual 
    void g()
    {
        cout << "virtual void Base::g()" << endl;
    }
    virtual 
    void h()
    {
        cout << "virtual void Base::h()" << endl;
    }

private:
    long _base;
};

class Derived
:public Base
{
public:
    Derived(long base = 0, long derived = 0)
    :Base(base)
    ,_derived(derived)
    {
        cout << "Derived(long = 0, long = 0)" << endl;
    }
    ~Derived()
    {
        cout << "~Derived()" << endl;
    }

    void f()
    {
        cout << "virtual void Derived::f()" << endl;
    }
    void g()
    {
        cout << "virtual void Derived::g()" << endl;
    }
    void h()
    {
        cout << "virtual void Derived::h()" << endl;
    }

private:
    long _derived;
};

int main()
{
    Derived derived(30, 35);
    printf("对象derived的地址: %p\n", &derived);
    printf("对象derived的地址: %p\n", (long*)&derived);
    printf("虚表的地址: %p\n", (long*)*(long*)&derived);
    printf("虚函数的地址: %p\n", (long*)*(long*)*(long*)&derived);

    printf("_base: %ld\n", *((long*)&derived + 1));
    printf("_derived: %ld\n", *((long*)&derived + 2));

    cout << endl << endl;
    typedef void (*Function)();
    Function pf;
    pf = (Function)*(long*)*(long*)&derived;
    pf();
    printf("第一个虚函数的地址: %p\n", pf);

    cout << endl;
    pf = (Function)*((long*)*(long*)&derived + 1);
    pf();
    printf("第二个虚函数的地址: %p\n", pf);

    cout << endl;
    pf = (Function)*((long*)*(long*)&derived + 2);
    pf();
    printf("第三个虚函数的地址: %p\n", pf);

    cout << endl << endl;
    Derived derived2(300, 350);
    printf("对象derived2的地址: %p\n", &derived2);
    printf("对象derived2的地址: %p\n", (long*)&derived2);
    printf("虚表的地址: %p\n", (long*)*(long*)&derived2);
    printf("虚函数的地址: %p\n", (long*)*(long*)*(long*)&derived2);
    return 0;
}

