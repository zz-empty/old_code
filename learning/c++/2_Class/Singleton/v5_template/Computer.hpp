#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include <iostream>
#include <string>

using std::string;

class Computer
{
public:
    Computer(const string brand, float price)
    :_brand(brand)
    ,_price(price)
    {}

    Computer(const Computer &rhs)
    :_brand(rhs._brand)
    ,_price(rhs._price)
    {}

    void print() const
    {
        std::cout << "brand: " << _brand << "<-----> price: " << _price << std::endl;
    }

    /* void setBrand(const char *brand); */
    /* void setPrice(int price); */

    ~Computer() = default;
private:
    string _brand;
    float  _price;
};

#endif
