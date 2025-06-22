#include "rectangle.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

void Rectangle::display() const
{
    cout << "--------perimeter : " << perimeter()
         << ", area : " << area() << "--------" << endl;
}

bool Rectangle::reset(double length, double wide)
{
    if (length > 0 && wide > 0) {
        _length = length;
        _wide = wide;
        return true;
    }
    return false;
}

}//end of namespace wd
