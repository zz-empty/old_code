#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__


namespace wd
{

class Rectangle
{
public:
    Rectangle(double length = 0, double wide = 0)
    :_length(length)
    ,_wide(wide)
    {}

    double perimeter() const {  return (_length + _wide) * 2;   }
    double area() const {   return _length * _wide;     }
    void display() const;
    bool reset(double length, double wide);

private:
    double _length;
    double _wide;
};

}//end of namespace wd


#endif
