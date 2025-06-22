#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::copy;
using std::ostream_iterator;
using std::count;
using std::find;

void print(int &val)
{
    ++val;
    cout << val << " ";
}

void test()
{
    vector<int> number = {3, 2, 1, 5, 9, 3, 3, 5, 9, 8, 7, 6, 5};

    cout << "---------test for_each----------" << endl;
    /* for_each(number.begin(), number.end(), print); */
    for_each(number.begin(), number.end(), [](int &val){
             ++val;
             cout << val << " ";
             });
    cout << endl;

    cout << "number = ";
    copy(number.begin(), number.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << endl;
    cout << "---------test count------------" << endl;
    cout << "number(4) cnt = " << count(number.begin(), number.end(), 4) << endl;

    cout << endl;
    cout << "---------test find-----------" << endl;
    auto ret = find(number.begin(), number.end(), 10);
    if (ret == number.end()) {
        cout << "Not find the elem in vector" << endl;
    }
    else {
        cout << *ret << endl;
    }

    cout << endl;
    cout << "--------test sort------------" << endl;
    std::sort(number.begin(), number.end());
    cout << "number = ";
    copy(number.begin(), number.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    test();
    return 0;
}

