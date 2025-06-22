#include "wordInstead.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;

namespace myfunc
{

WordInstead::WordInstead(const string &filename, const string &rule)
{
    //将规则文件存入map
    dealRule(rule);
    dealFile(filename);
}

void WordInstead::dealFile(const string &filename)
{
    //读取文件中的每一个单词，作为unordered_map的键，值是每行的单词数
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        std::cerr << "the file is not good!" << endl;
    }

    string line;
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        string word;
        bool firstword = true;
        while (iss >> word) {
            if (firstword) {
                firstword = false;
            }
            else {
                cout << " ";
            }
            cout << transform(word);
            
        }
        cout << endl;
    }

    /* displayFile(); */

    ifs.close();
}
const string &WordInstead::transform(const string &word)
{
    auto ret = _rule.find(word);
    if (ret != _rule.end()) {
        return ret->second;
    }
    else {
        return word;
    }
}

void WordInstead::dealRule(const string &rule)
{
    std::ifstream ifs(rule);
    //读取规则文件的每一行, 每行的第一个单词作为key，之后的作为值
    string line;
    string key;
    string val;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        if (iss >> key) {
            // 跳过第一个单词后的空白字符（如果有的话）
            iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

            // 读取剩余的所有字符到remainingWords
            std::getline(iss, val);
        } 
        //存入_rule
        _rule.insert({key, val});
    }

    /* displayRule(); */

    ifs.close();
}

void WordInstead::displayRule() const
{
    for (auto &elem : _rule) {
        cout << elem.first << "   \t" << elem.second << endl;
    }
}

void WordInstead::displayFile() const
{
    auto begin = _file.begin();
    for (; begin != _file.end(); ++begin) {
        cout << begin->second << endl;
    }
}

}// end of namespace wd
