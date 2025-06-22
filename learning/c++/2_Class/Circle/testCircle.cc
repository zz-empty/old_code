#include "Circle.hpp"
#include "Cylinder.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;
    Circle c(10);
    c.show();
}

void test1()
{
    using namespace wd;
    Cyclinder cyc(5, 6);
    cyc.showVolume();
}

int main()
{
    test1();
    return 0;
}

