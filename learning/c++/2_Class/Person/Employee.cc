#include "Employee.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

void Employee::display() const
{
    cout << "-------THE EMPLOYEE-------" << endl;
    Person::display();
    cout << "department: " << _department << endl;
    cout << "salary : " << _salary << endl << endl;
}

}//end of namespace wd
