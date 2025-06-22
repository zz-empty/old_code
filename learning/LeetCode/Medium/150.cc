#include <iostream>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "+" || tokens[i] == "-" ||
                tokens[i] == "*" || tokens[i] == "/") {
                long long num1 = st.top();
                st.pop();
                long long num2 = st.top();
                st.pop();

                if (tokens[i] == "+") {
                    st.push(num1 + num2);
                }
                else if (tokens[i] == "-") {
                    st.push(num2 - num1);
                }
                else if (tokens[i] == "*") {
                    st.push(num1 * num2);
                }
                else {
                    st.push(num2 / num1);
                }
            }
            else {
                st.push(std::stoll(tokens[i]));
            }
        }

        int result = st.top();
        st.pop();
        return result;
    }
};

int main()
{
    return 0;
}

