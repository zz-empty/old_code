#include "Circle.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{


double Circle::getArea() const
{
    return 3.14 * _radius * _radius;
}

double Circle::getPerimeter() const
{
    return 2 * 3.14  * _radius;
}

void Circle::show() const
{
    cout << "----radius : " << _radius << endl 
         << "----area : " << getArea() << endl
         << "----perimeter : " << getPerimeter() << endl; 
}

}//end of namespace wd
