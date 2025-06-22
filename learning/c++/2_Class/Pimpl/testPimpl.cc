#include "Pimpl.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;

    Line l1(2, 4, 3, 5);
    l1.printLine();

}

int main()
{
    test0();
    return 0;
}

