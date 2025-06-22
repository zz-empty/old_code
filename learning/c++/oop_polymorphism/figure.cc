#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

class Figure
{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;
};

class Circle
:public Figure
{
public:
    explicit Circle(double radius)
    :_radius(radius)
    {
    }

    void display() const override
    {
        cout << "Circle";
    }

    double area() const override
    {
        return 3.14159 * _radius * _radius;
    }
private:
    double _radius;
};

class Rectangle
:public Figure
{
public:
    explicit Rectangle(double length, double width) 
    :_length(length)
    ,_width(width)
    {

    }

    void display() const override
    {
        cout << "Rectangle";
    }
    
    double area() const override
    {
        return _length * _width;
    }
private:
    double _length;
    double _width;
};

class Triangle
:public Figure
{
public:
    Triangle(double a, double b, double c)
    :_a(a)
    ,_b(b)
    ,_c(c)
    {
        
    }

    void display() const override
    {
        cout << "Triangle";
    }

    double area() const override
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
    fig.display();
    cout << "'s area is : " << fig.area() << endl;
}

int main()
{
    Circle circle(10);
    Rectangle rectangle(10, 5);
    Triangle triangle(3, 4, 5);

    func(circle);
    func(rectangle);
    func(triangle);
    return 0;
}

