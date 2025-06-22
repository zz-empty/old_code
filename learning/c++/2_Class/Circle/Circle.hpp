#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

namespace wd
{

class Circle
{
public:
    Circle() = default;

    Circle(double r)
    :_radius(r)
    {}

    double getArea() const;
    double getPerimeter() const;
    void show() const;

private:
    double _radius;
};

}//end of namespace wd

#endif
