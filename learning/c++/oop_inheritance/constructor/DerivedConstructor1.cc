#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base()
    {
        cout << "Base()" << endl;
    }
private:
    double _base;
};

class Derived
:public Base
{
public:
    Derived(double derived)
    :_dderived(derived)
    {
        cout << "Derived(double)" << endl;
    }
private:
    double _dderived;
};

int main()
{
    Derived d(10);
    return 0;
}

