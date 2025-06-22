#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;
using std::string;

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> cuts;
        int n = 0;      //删除的字符数
        for (int i = 0; i < s.size(); ++i) {
            //栈非空，匹配
            if (!cuts.empty() && cuts.top() == s[i]) {
                cuts.pop();
                n += 2;
            }
            else {
                cuts.push(s[i]);
                s[i - n] = s[i];
            }
        }

        return s.substr(0, s.size() - n);
    }
};

int main()
{
    return 0;
}

