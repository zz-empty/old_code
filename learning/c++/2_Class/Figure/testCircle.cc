#include "Circle.hpp"
#include "Cylinder.hpp"
#include <iostream>

using std::cout;
using std::endl;

using namespace wd;

void showFigure(Circle *c) 
{
    cout << "name : " << c->getName() << endl;
    c->show();
}

void test0()
{
    Circle c(10);
    Cyclinder cyc(5, 6);

    showFigure(&c);
    cout << endl;
    showFigure(&cyc);
}


int main()
{
    test0();
    return 0;
}

