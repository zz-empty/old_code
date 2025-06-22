#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
#if 0
    Base()
    :_dbase(0)
    {
        cout << "Base()" << endl;
    }
#endif
    Base(double base)
    :_dbase(base)
    {
        cout << "Base(double)" << endl;
    }
private:
    double _dbase;
};

class Derived
:public Base
{
public:
    Derived()
    :Base(0)
    ,_dderived(0)
    {
        cout << "Derived()" << endl;
    }
#if 1
    Derived(double derived)
    :Base(derived)
    ,_dderived(derived)
    {
        cout << "Derived(double)" << endl;
    }
#endif
private:
    double _dderived;
};

int main()
{
    Derived d;
    return 0;
}

