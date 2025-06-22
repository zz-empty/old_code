#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

class Rectangle
{
public:
    Rectangle(float len, float wide);
    ~Rectangle();

    bool setLen(float len);
    bool setWide(float wide);

    float perimeter();
    float area();
private:
    float _len;
    float _wide;
};

#endif
