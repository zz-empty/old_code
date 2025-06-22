#include <math.h>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::string;

template<typename Container>
void display(const Container &c)
{
    for (auto &elem : c) {
        cout << elem.first << " " << elem.second << endl;
    }
    cout << endl;
}

void test()
{
    map<int, string> addr = {
        {1, "wuhan"},
        {2, "beijing"},
        {3, "chongqing"},
        std::pair<int, string>(7, "tianjin"),
        std::make_pair(4, "nanjing"),
        std::make_pair(6, "山东")
    };
    display(addr);

    cout << endl;
    cout << "--------------test map::insert--------------" << endl;
    std::pair<map<int,string>::iterator, bool> ret = addr.insert(std::pair<int, string>(9, "henan"));
    if (ret.second) {
        cout << "insert succeed, ";
        cout << ret.first->first << " " << ret.first->second << endl;
    }
    else {
        cout << "insert fail" << endl;
    }
    
    addr.insert({10, "jixi"});
    display(addr);

    cout << endl;
    cout << "---------test 下标访问-------------" << endl;
    cout << "addr[20] = " << addr[20] << endl;
    cout << "addr[2] = " << addr[2] << endl;
    display(addr);

    addr[20] = "gansu";
    display(addr);
    
}


class Point
{
public:
    Point(int ix = 0, int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {

    }


    int getX() const
    {
        return _ix;
    }
    int getY() const
    {
        return _iy;
    }

    double getDistance() const
    {
        return hypot(_ix, _iy);
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs.getX() << "," << rhs.getY() << ")" ;
    return os;
}


void test_class()
{
    map<string, Point> addr = {
        {"beijing", Point(1, 1)},
        {"shanghai", Point(2, 3)},
        std::pair<string, Point>("guangzhou", Point(3, 2)),
        std::make_pair<string, Point>("shenzhen", Point(3, 3))
    };

    display(addr);

    cout << endl;
    cout << "addr[\"shenyang\"] = " << addr["shenyang"] << endl;
    cout << "addr[\"beijing\"] = " << addr["beijing"] << endl;
    display(addr);
    addr["shenyang"] = Point(4, 5);
    display(addr);
}

int main()
{
    /* test(); */
    test_class();
    return 0;
}

