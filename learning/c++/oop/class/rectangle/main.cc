#include "rectangle.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    Rectangle rec(3,4);
    cout << "---rec perimeter is " << rec.perimeter() << ", "
         << "rec area is " << rec.area() << "---" << endl;
    return 0;
}

