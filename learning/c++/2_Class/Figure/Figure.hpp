#ifndef __FIGURE_HPP__
#define __FIGURE_HPP__

#include <string>

namespace wd
{

class Figure
{
protected:
    virtual double getArea( ) const = 0;
    virtual std::string getName( ) const = 0;
    virtual void show() const = 0;
    
    std::string _name;
};


}// end of namespace wd

#endif
