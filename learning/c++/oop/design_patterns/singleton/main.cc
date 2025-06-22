#include "singleton.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    cout << "p = " << Singleton::getInstance() << endl;

    Singleton *pS1 = Singleton::getInstance();
    Singleton *pS2 = Singleton::getInstance();

    cout << "pS1 = " << pS1 << endl;
    cout << "pS2 = " << pS2 << endl;

    Singleton::destroy();
    Singleton::destroy();

    return 0;
}
