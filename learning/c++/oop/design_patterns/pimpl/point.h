#ifndef __POINT_H__
#define __POINT_H__

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    void printLine();
    ~Line();
    class PointPimpl;
private:
    PointPimpl *_pimpl;
};

#endif
