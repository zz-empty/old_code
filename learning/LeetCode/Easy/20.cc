#include <iostream>
#include <string>
#include <stack>

using std::cout;
using std::endl;
using std::string;
using std::stack;

class Solution {
public:
    //判断括号匹配是否正确
    bool isValid(string s) {
        //三种情况：左括号多余，右括号多余，匹配错误括号
        stack<char> st;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                st.push(')');
            }
            else if (s[i] == '[') {
                st.push(']');
            }
            else if (s[i] == '{') {
                st.push('}');
            }
            else if (st.empty() || st.top() != s[i]) {
                //右括号多余时
                //括号无法匹配
                return false;
            }
            else {
                //括号匹配成功，弹栈
                st.pop();
            }
        }

        //遍历完，如果stack还有元素则无效
        return st.empty();
    }
};

int main()
{
    return 0;
}

