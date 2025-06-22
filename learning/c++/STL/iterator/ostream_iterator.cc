#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::ostream_iterator;

void test()
{
    vector<int> number = {3, 2, 4, 1, 9};

    ostream_iterator<int> osi(cout, " ");
    copy(number.begin(), number.end(), osi);
    cout << endl;
}

int main()
{
    test();
    return 0;
}

