#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::bind1st;

bool func(int val) 
{
    return val > 5;
}

void test()
{
    vector<int> number = { 2, 3, 1, 1, 2, 4, 5, 2, 9, 8, 6, 1 };
    std::copy(number.begin(), number.end(),std::ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << endl;
    cout << "---------------test remove_if----------------" << endl;
    /* auto ret = std::remove_if(number.begin(), number.end(), func); */
    auto ret = std::remove_if(number.begin(), number.end(), [](int val) {
                              return val > 5;
                              });
    number.erase(ret, number.end());
    std::copy(number.begin(), number.end(),std::ostream_iterator<int>(cout, " "));
    cout << endl;
}

void test_bind1st()
{
    vector<int> number = { 2, 3, 1, 1, 2, 4, 5, 2, 9, 8, 6, 1 };
    std::copy(number.begin(), number.end(),std::ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << endl;
    cout << "---------------test remove_if & bind1st----------------" << endl;
    auto it = std::remove_if(number.begin(), number.end(), bind1st(std::less<int>(), 5));
    number.erase(it, number.end());
    std::copy(number.begin(), number.end(),std::ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    /* test(); */
    test_bind1st();
    return 0;
}

