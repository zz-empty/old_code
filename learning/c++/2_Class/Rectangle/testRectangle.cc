#include "rectangle.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;

    Rectangle rec(10, 20);
    rec.display();

    cout << endl;
    Rectangle rec2;
    rec2.reset(5, 6);
    rec2.display();
}

int main()
{
    test0();
    return 0;
}

