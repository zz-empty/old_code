#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    //反转字符串
    void reverse(string &s, int start, int end) {
        for (int i = start, j = end - 1; i < j; ++i, --j) {
            char c = s[i];
            s[i] = s[j];
            s[j] = c;
        }
    }

    //去除字符串中的所有空格，并在单词之间加上空格作为分割
    void removeExactSpace(string &s) {
        int slow = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != ' ') {
                if (slow != 0) {
                    s[slow++] = ' '; //单词间加上空格
                }

                //设置单词
                while (i < s.size() && s[i] != ' ') {
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow);//去掉slow后面的字符
    }


    string reverseWords(string s) {
        removeExactSpace(s);
        reverse(s, 0, s.size());

        int start = 0;  //每个单词的起始下标
        for (int i = 0; i <= s.size(); ++i) {
            if (i == s.size() || s[i] == ' ') {
                reverse(s, start, i);
                start = i + 1;
            }
        }

        return s;
    }
};

int main()
{
    return 0;
}

