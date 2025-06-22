#include <iostream>
#include <string>
#include <stack>

using std::cout;
using std::endl;
using std::string;
using std::stack;

class Solution {
public:
    bool isValid(string s) {
        stack<char> tmp;

        if (s.size() <= 1) {
            return false;
        }
        
        for (size_t idx = 0; idx < s.size(); ++idx) {
            switch(s[idx]) {
            case '(':
            case '[':
            case '{':
                tmp.push(s[idx]);
                continue;

            case ')':
                if (tmp.size() && '(' == tmp.top()) {
                    tmp.pop();
                    continue;
                }
                else {
                    return false;
                }
            case ']':
                if (tmp.size() && '[' == tmp.top()) {
                    tmp.pop();
                    continue;
                }
                else {
                    return false;
                }
            case '}':
                if (tmp.size() && '{' == tmp.top()) {
                    tmp.pop();
                    continue;
                }
                else {
                    return false;
                }
            }
        }

        return tmp.empty();
    }
};
