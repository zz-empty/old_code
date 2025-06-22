#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    //判断两个字符串是否是有效异位词
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        int hash[26] = {0};
        for (size_t i = 0; i < s.size(); ++i) {
            hash[s[i] - 'a']++;
        }
        for (size_t i = 0; i < t.size(); ++i) {
            hash[t[i] - 'a']--;
        }

        for (int i = 0; i < 26; ++i) {
            if (hash[i]) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    return 0;
}

