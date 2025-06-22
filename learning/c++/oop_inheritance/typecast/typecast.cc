#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(double base)
    :_dbase(base)
    {
        cout << "Base(double)" << endl;
    }
    void print() const
    {
        cout << "Base::_dbase =  " << _dbase << endl;
    }
    ~Base()
    {
        cout << "~Base()" << endl;
    }
private:
    double _dbase;
};

class Derived
:public Base
{
public:
    Derived(double base = 0, double derived = 0) 
    : Base(base)
    ,_dderived(derived)
    {
        cout << "Derived(double = 0, double = 0)" << endl;
    }
    void show() const
    {
        cout << "Derived::_dderived =  " << _dderived << endl;
    }
    ~Derived()
    {
        cout << "~Derived()" << endl;
    }
private:
    double _dderived;
};

int main()
{
    Base base(11.11);
    base.print();

    cout << endl;
    Derived derived(22.22, 33.33);
    derived.show();

    cout << endl << "从派生类向基类转换" << endl;
    base = derived;
    base.operator=(derived);

    Derived *derived1 = static_cast<Derived*>(&base);
    return 0;
}

