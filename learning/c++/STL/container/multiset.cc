#include <math.h>
#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::multiset;
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
    /* multiset<int> number(arr, arr + 10); */
    multiset<int, std::less<int>> number(arr, arr + 10);
    /* multiset<int, std::greater<int>> number(arr, arr + 10); */
    display(number);

    cout << endl;
    cout << "-------test multiset::count-------" << endl;
    size_t cnt1 = number.count(9);
    size_t cnt2 = number.count(99);
    cout << "cnt1 = " << cnt1 << endl;
    cout << "cnt2 = " << cnt2 << endl;
    
    cout << endl;
    cout << "-------test multiset::find--------" << endl;
    auto it = number.find(80);
    if (it == number.end())  {
        cout << "this elem is not exist!" << endl;
    }
    else {
        cout << *it << endl;
    }

#if 1
    cout << endl;
    cout << "--------test multiset::insert--------" << endl;
    auto ret = number.insert(17);
    cout << *ret << " insert succeed" << endl;
#endif

    cout << endl;
    vector<int> vec = {31, 8, 13, 24, 51};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl;
    std::initializer_list<int> il = { 22, 33, 44, 55 };
    number.insert(il);
    display(number);

    cout << endl;
    cout << "-------test multiset::erase-------" << endl;
    it = number.begin();
    ++it;
    ++it;
    number.erase(it);
    display(number);
    

    cout << endl;
    cout << "--------test lower_bound--------" << endl;
    auto it4 = number.lower_bound(8);
    cout << "lower_bound(8) = " << *it4 << endl;
    auto it5 = number.upper_bound(8);
    cout << "upper_bound(8) = " << *it5 << endl;
    while (it4 != it5) {
        cout << *it4 << " ";
        ++it4;
    }
    cout << endl;

    cout << endl;
    cout << "--------test equal_range--------" << endl;
    auto r = number.equal_range(3);
    while (r.first != r.second) {
        cout << *r.first << " ";
        ++r.first;
    }
    cout << endl;
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
    /* multiset<Point, std::less<Point>> ps = { */
    multiset<Point, std::greater<Point>> ps = {
        Point(1, 2),
        Point(1, 2),
        Point(3, -2),
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

