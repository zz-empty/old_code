#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

namespace wd
{

class Person
{
public:
    Person(const string &name = nullptr, const size_t age = 0)
    :_name(name)
    ,_age(age)
    {}

    void display() const;

protected:
    string _name;
    size_t _age;
};

}//end of namespace wd

#endif
