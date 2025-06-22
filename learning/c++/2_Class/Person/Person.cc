#include "Person.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

void Person::display() const
{
    cout << "name : " << _name << endl;
    cout << "age : " << _age << endl;
}

}// end of namespace wd
