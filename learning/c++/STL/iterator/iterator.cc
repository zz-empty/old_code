#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::ostream_iterator;
using std::insert_iterator;
using std::istream_iterator;
using std::back_insert_iterator;
using std::front_insert_iterator;
using std::copy;

void test()
{
    vector<int> numberVec = {5, 9, 4, 8, 3};
    list<int> numberList = {5, 2, 1, 4, 6, 9, 0};

    copy(numberList.begin(), numberList.end(), back_insert_iterator<vector<int>>(numberVec));
    copy(numberVec.begin(), numberVec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << endl << endl;
    copy(numberVec.begin(), numberVec.end(), front_insert_iterator<list<int>>(numberList));
    copy(numberList.begin(), numberList.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    test();
    return 0;
}

