#include "Base.hpp"
#include <iostream>

using std::cout;
using std::endl;


namespace  wd
{


std::ostream &operator<<(std::ostream &os, const Base &rhs)
{
    os << rhs._i;
    return os;
}

bool operator==(const Base &lhs, int i)
{
    return lhs._i == i;
}

Base operator+(const Base &lhs, const Base &rhs)
{
    return Base(lhs.get() + rhs.get());
}

}//end of namespace wd
