#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    void reverseString(vector<char>& s) {
        char tmp;
        for (int i = 0, j = s.size() - 1; i < s.size() / 2; ++i, --j) {
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
        }
    }
};

int main()
{
    return 0;
}

