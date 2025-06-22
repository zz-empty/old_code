#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "Figure.hpp"
#include <string>

using std::string;

namespace wd
{

class Circle
:public Figure
{
public:
    Circle() = default;

    Circle(double r)
    :_radius(r)
    {}

    double getRadius() const    {   return _radius;     }
    double getArea() const;
    double getPerimeter() const;
    virtual string getName() const     {   return string("Circle");    }

    void show() const;

private:
    double _radius;
};

}//end of namespace wd

#endif
