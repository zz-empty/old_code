#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(long base = 0)
    :_pbase(base)
    {
        cout << "Base(long)" << endl;
    }

    virtual
    void print()
    {
        cout << "Base::_pbase = " << _pbase << endl;
    }

    ~Base()
    {
        cout << "~Base()" << endl;
    }
private:
    long _pbase;
};

class Derived
:public Base
{
public:
    Derived(long base = 0, long derived = 0)
    :Base(base)
    ,_pderived(derived)
    {
        cout << "Derived(long, long)" << endl;
    }

    void print()
    {
        cout << "Derived::_pderived = " << _pderived << endl;
    }

    ~Derived()
    {
        cout << "~Derived()" << endl;
    }
private:
    long _pderived;
};

void func(Base &ptr)
{
    ptr.print();
}

void test_virual()
{
    Base base(20);
    base.print();
    cout << "sizeof(base) = " << sizeof(base) << endl;
    cout << endl;

    Derived derived(30, 40);
    derived.print();
    cout << "sizeof(derived) = " << sizeof(derived) << endl;
    cout << endl;
}

void test_virual2()
{
    Base base(10);
    Derived derived(33, 44);

    Base *ptr = &base;
    ptr->print();
    cout << endl;

    ptr = &derived;
    ptr->print();
    cout << endl;
}

void test_virual3()
{
    Base base(10);
    Derived derived(33, 44);

    cout << endl;
    func(base);
    cout << endl;
    func(derived);
}

int main()
{
    /* test_virual(); */
    /* test_virual2(); */
    test_virual3();
    return 0;
}

