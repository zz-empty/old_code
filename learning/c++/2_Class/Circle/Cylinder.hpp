#ifndef __CYLINDER_HPP__
#define __CYLINDER_HPP__

#include "Circle.hpp"

namespace wd
{

class Cyclinder
:public Circle
{
public:
    Cyclinder(double r, double h)
    :Circle(r)
    ,_high(h)
    {}

    double getVolume() const;
    void showVolume() const;

private:
    double _high;
};

}// end of namespace wd

#endif
