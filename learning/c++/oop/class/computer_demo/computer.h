#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include <iostream>
#include <string>

using std::string;

class Computer
{
public:
    Computer();
    Computer(const char* brand, float price);
    ~Computer();
    Computer(const Computer &rhs);
    Computer &operator=(const Computer &rhs);

    void print();
    void setBrand(const char *brand);
    void setPrice(int price);

    static void printTotalPrice();

    void destroy();

private:
    char *_brand;
    float  _price;
    static float _totalPrice;
};

#endif
