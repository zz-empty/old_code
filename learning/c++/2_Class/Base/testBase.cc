#include "Base.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);

    cout << ( x + y == j - i ) << endl;
}

int main()
{
    test0();
    return 0;
}

