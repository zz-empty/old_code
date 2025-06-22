#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    //判断字符串是否由字串构成
    //枚举法
    bool repeatedSubstringPattern_baoli(string s) {
        int n = s.length();
        for (int i = 0; i <= n / 2; ++i) {
            if (n % i == 0) {   //子串的长度是s的约数
                string pattern = s.substr(0, i);
                bool match = true;
                //检查子串能否复制成s
                for (int j = i; j < n; j += i) {
                    if (s.substr(j, i) != pattern) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return true;
                }
            }
        }

        return false;
    }

    void getNext(int *next, const string &s) {
        next[0] = 0;
        int j = 0;

        for (int i = 1; i < s.length(); ++i) {
            while (j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }

    bool repeatedSubstringPattern(string s) {
        if (s.size() == 0) {
            return false;
        }

        int next[s.size()];
        getNext(next, s);
        int len = s.length();

        //最长相等前后缀不包含的子串长度，可以被len整除时，就表明s是由这个子串构成的
        if (next[len - 1] != 0 && len % (len - (next[len - 1])) == 0) {
            return true;
        }
        return false;
    }
};

int main()
{
    return 0;
}

