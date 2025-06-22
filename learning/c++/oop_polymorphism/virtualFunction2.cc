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

    virtual
    void func1()
    {
        this->print();
    }
    
    void func2()
    {
        Base::print();
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

    void print() override
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
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(Derived) = " << sizeof(Derived) << endl;

    Base base(20);
    base.print();
    Derived derived(30, 40);
    derived.print();

    cout << endl << endl;
    Base *pbase1 = &base;
    pbase1->func1();
    pbase1->func2();
    
    cout << endl;
    Base *pbase2 = &derived;
    pbase2->func1();
    pbase2->func2();
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


int main()
{
    test_virual();
    /* test_virual2(); */
    return 0;
}

