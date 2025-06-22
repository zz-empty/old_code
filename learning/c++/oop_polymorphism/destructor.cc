#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(const char *pbase)
    :_pbase(new char[strlen(pbase) + 1]())
    {
        cout << "Base(const char*)" << endl;
        strcpy(_pbase, pbase);
    }

    virtual
    ~Base()
    {
        cout << "~Base()" << endl;
        if (_pbase) {
            delete [] _pbase;
            _pbase = nullptr;
        }
    }

    virtual
    void print() const
    {
        cout << "Base::_pbase: " << _pbase << endl;
    }
private:
    char *_pbase;
};

class Derived
:public Base
{
public:
    Derived(const char *pbase, const char *pderived)
    :Base(pbase)
    ,_pderived(new char[strlen(pderived) + 1]())
    {
        cout << "Derived(const char*)" << endl;
        strcpy(_pderived, pderived);
    }
    ~Derived()
    {
        cout << "~Derived()" << endl;
        if (_pderived) {
            delete [] _pderived;
            _pderived = nullptr;
        }
    }

    virtual
    void print() const override
    {
        cout << "Derived::_pderived: " << _pderived << endl;
    }
private:
    char *_pderived;
};

int main()
{
    Base *pb = new Derived("hello", "world");
    pb->print();

    delete pb;
    return 0;
}

