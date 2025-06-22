#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2 * k) {
            if (i + k < s.size()) {
                std::reverse(s.begin() + i, s.begin() + i + k);
            }
            else {
                std::reverse(s.begin() + i, s.end());
            }
        }
        return s;
    }
};

int main()
{
    return 0;
}

