#ifndef __EMPLOYEE_HPP__
#define __EMPLOYEE_HPP__

#include "Person.hpp"

namespace wd
{

class Employee
:public Person
{
public:
    Employee(const string &name, const size_t age, const string &department, const double salary)
    :Person(name, age)
    ,_department(department)
    ,_salary(salary)
    {}

    void display() const;
    double getSalary() const  {   return _salary;     }

private:
    string _department;
    double _salary;
};

}//end of namespace wd

#endif
