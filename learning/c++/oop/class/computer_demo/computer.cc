#include "computer.h"
#include <string.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

float Computer::_totalPrice = 0.0;

Computer::Computer()
{
    cout << "Computer()" << endl;
}

Computer::Computer(const char* brand, float price)
: _brand(new char[strlen(brand) + 1]())
, _price(price)
{
    cout << "Computer(const char*, float)" << endl;
    strcpy(_brand, brand);

    _totalPrice += _price;
}

void Computer::destroy()
{
    this->~Computer();
}

Computer::~Computer()
{
    cout << "~Computer()" << endl;
    //clear member
    if (_brand) {
        cout << "delete [] _brand" << endl;
        delete [] _brand;
        _brand = nullptr; //prevent wild_pointer
    }

    _totalPrice -= _price;
}

Computer::Computer(const Computer &rhs)
: _brand(new char[strlen(rhs._brand) + 1])
, _price(rhs._price)
{
    cout << "Computer(const Computer &)" << endl;
    strcpy(_brand, rhs._brand);
}

Computer& Computer::operator=(const Computer &rhs)
{
    cout << "Computer &operator=(const Computer &)" << endl;
    if (this != &rhs) { //自复制

        if (strlen(_brand) < strlen(rhs._brand)) {
            delete [] _brand;   //释放左操作数
            _brand = nullptr;
            _brand = new char[strlen(rhs._brand) + 1]();    //深拷贝
        }

        strcpy(_brand, rhs._brand);
        _price = rhs._price;
    }
    return *this;   //返回对象本身
}

void Computer::print()
{
    printf("---_brand = %p\n", _brand);
    cout << "------Brand: " << _brand << ", "
        << "Price: " << _price << "------" << endl;
}

void Computer::setBrand(const char *brand)
{
    strcpy(_brand, brand);
}

void Computer::setPrice(int price)
{
    _price = price;
}

void Computer::printTotalPrice()
{
    cout << "totalPrice = " << _totalPrice << endl;
}
