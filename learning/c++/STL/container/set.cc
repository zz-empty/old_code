#include <math.h>
#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;

template<typename Container>
void display(const Container &c)
{
    for (auto &elem : c) {
        cout << elem << " ";
        /* cout << elem ; */
    }
    cout << endl;
}

void test()
{
    int arr[10] = { 3, 2, 1, 3, 5, 6, 8, 9 };
    /* set<int> number(arr, arr + 10); */
    /* set<int, std::less<int>> number(arr, arr + 10); */
    set<int, std::greater<int>> number(arr, arr + 10);
    display(number);

    cout << endl;
    cout << "-------test set::count-------" << endl;
    size_t cnt1 = number.count(9);
    size_t cnt2 = number.count(99);
    cout << "cnt1 = " << cnt1 << endl;
    cout << "cnt2 = " << cnt2 << endl;
    
    cout << endl;
    cout << "-------test set::find--------" << endl;
    auto it = number.find(80);
    if (it == number.end())  {
        cout << "this elem is not exist!" << endl;
    }
    else {
        cout << *it << endl;
    }

    cout << endl;
    cout << "--------test set::insert--------" << endl;
    std::pair<set<int>::iterator, bool> ret = number.insert(17);
    if (ret.second) {
        cout << *ret.first << " insert succeed" << endl;
    }
    else {
        cout << "insert fail" << endl;
    }

    cout << endl;
    vector<int> vec = {31, 8, 13, 24, 51};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl;
    std::initializer_list<int> il = { 22, 33, 44, 55 };
    number.insert(il);
    display(number);

    cout << endl;
    cout << "-------test set::erase-------" << endl;
    it = number.begin();
    ++it;
    ++it;
    number.erase(it);
    display(number);
    
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

bool operator<(const Point &lhs, const Point &rhs)
{
    /* return lhs.getX() < rhs.getX(); */
    if (lhs.getDistance() < rhs.getDistance()) {
        return true;
    }
    else if (lhs.getDistance() == rhs.getDistance()) {
        if (lhs.getX() < rhs.getX()) {
            return true;
        }
        else if (lhs.getX() == rhs.getX()) {
            if (lhs.getY() < rhs.getY()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool operator>(const Point &lhs, const Point &rhs)
{
    if (lhs.getDistance() > rhs.getDistance()) {
        return true;
    }
    else if (lhs.getDistance() == rhs.getDistance()) {
        if (lhs.getX() < rhs.getX()) {
            return true;
        }
        else if (lhs.getX() == rhs.getX()) {
            if (lhs.getY() > rhs.getY()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void test_class()
{
    /* set<Point, std::less<Point>> ps = { */
    set<Point, std::greater<Point>> ps = {
        Point(1, 2),
        Point(3, -2),
        Point(5, 3),
        Point(-1, 3),
        Point(-4, 3),
        Point(3, 3),
        Point(0, 3),
        Point(1, -7),
        Point(5, 2)
    };

    display(ps);
}

int main()
{
    /* test(); */
    test_class();
    return 0;
}

