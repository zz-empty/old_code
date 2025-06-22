# ifndef COMPUTER_H__
# define COMPUTER_H__

# include <iostream>
using namespace std;

class Computer
{
public:
    Computer(const string &s, double price)
        :_brand(s)
         ,_price(price)
    {}
    void print()const
    {
        cout << "brand : " << _brand << " " << "price : " << _price << endl;
    }
    ~Computer() = default;
private:
    string _brand;
    double _price;
};

# endif
