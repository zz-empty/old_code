#include <math.h>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::function;

class Figure
{
public:
    /* typedef function<void()> DisplayCallback1; */

    //c++中的重定义类型
    using DisplayCallback = function<void()>; 
    using AreaCallback = function<double()>; 

    //定义两个函数指针
    DisplayCallback _displayCallback;
    AreaCallback _areaCallback;

    //注册回调函数
    void setDisplayCallback(DisplayCallback &&bc) 
    {
        _displayCallback = std::move(bc);
    }

    void setAreaCallback(AreaCallback &&ac)
    {
        _areaCallback = std::move(ac);
    }

    //执行回调函数
    void handDisplayCallback() const
    {
        if (_displayCallback) {
            _displayCallback();
        }
    }

    double handAreaCallback() const
    {
        if (_areaCallback) {
            return _areaCallback();
        }
        else {
            return 0;
        }
    }

#if 0
    virtual void display() const = 0;
    virtual double area() const = 0;
#endif
};

class Circle
{
public:
    explicit Circle(double radius)
    :_radius(radius)
    {
    }

    void display() const 
    {
        cout << "Circle";
    }

    double area() const 
    {
        return 3.14159 * _radius * _radius;
    }
private:
    double _radius;
};

class Rectangle
{
public:
    explicit Rectangle(double length, double width) 
    :_length(length)
    ,_width(width)
    {

    }

    void display() const 
    {
        cout << "Rectangle";
    }
    
    double area() const 
    {
        return _length * _width;
    }
private:
    double _length;
    double _width;
};

class Triangle
{
public:
    Triangle(double a, double b, double c)
    :_a(a)
    ,_b(b)
    ,_c(c)
    {
        
    }

    void display(int a) const 
    {
        cout << "Triangle";
    }

    double area() const 
    {
        double p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }
private:
    double _a;
    double _b;
    double _c;
};

void func(const Figure &fig) 
{
    fig.handDisplayCallback();
    cout << "'s area is : " << fig.handAreaCallback() << endl;
}

void test()
{
    Circle circle(10);
    Rectangle rectangle(10, 5);
    Triangle triangle(3, 4, 5);

    Figure fig;
    fig.setDisplayCallback(std::bind(&Rectangle::display, &rectangle));
    fig.setAreaCallback(std::bind(&Rectangle::area, &rectangle));
    func(fig);

    cout << endl;
    fig.setDisplayCallback(std::bind(&Circle::display, &circle));
    fig.setAreaCallback(std::bind(&Circle::area, &circle));
    func(fig);

    cout << endl;
    fig.setDisplayCallback(std::bind(&Triangle::display, &triangle, 1));
    fig.setAreaCallback(std::bind(&Triangle::area, &triangle));
    func(fig);
}

int main()
{
    test();
    return 0;
}

