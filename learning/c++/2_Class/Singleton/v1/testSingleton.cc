#include "Singleton.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;
    AutoRelease au;

    cout << "p = " << Singleton::getInstance() << endl;

    Singleton *ps1 = Singleton::getInstance();
    Singleton *ps2 = Singleton::getInstance();

    Singleton *ps3 = ps1;

    cout << "ps1 = " << ps1 << endl;
    cout << "ps2 = " << ps2 << endl;
    cout << "ps3 = " << ps3 << endl;

}

int main()
{
    test0();
    return 0;
}

