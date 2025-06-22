#include "Cylinder.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

double Cyclinder::getVolume() const
{
    return getArea() * _high;
}

void Cyclinder::show() const
{
    Circle::show();
    cout << "----volume : " << getVolume() << endl;
}

}// end of namespace wd
