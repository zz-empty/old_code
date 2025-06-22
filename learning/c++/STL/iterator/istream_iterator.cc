#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;

void test()
{
    vector<int> number;
    istream_iterator<int> isi(std::cin);

    copy(isi, istream_iterator<int>(), std::back_inserter(number));

    cout << endl << endl;
    copy(number.begin(), number.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    test();
    return 0;
}

