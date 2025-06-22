#ifndef __PIMPL_HPP__
#define __PIMPL_HPP__


namespace wd
{

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine();
    class PointPimpl;
private:
    PointPimpl *_ppl;
};

}//end of namespace wd


#endif
