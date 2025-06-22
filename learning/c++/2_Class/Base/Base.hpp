#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <iostream>


namespace wd
{


class Base
{
public:
    Base(int i) : _i(i) 
    {}

    int get() const  {   return _i;  };

    //<< + ==
    friend std::ostream &operator<<(std::ostream &os, const Base &rhs);
    friend bool operator==(const Base &lhs, int i);
private:
    int _i;
};

Base operator+(const Base &lhs, const Base &rhs);

}//end of namespace wd

#endif
