#ifndef __WORDINSTEAD_HPP__
#define __WORDINSTEAD_HPP__

#include <string>
#include <map>
#include <unordered_map>

using std::string;

namespace myfunc
{

class WordInstead
{
public:
    WordInstead(const string &filename, const string &rule);
    void displayRule() const;
    void displayFile() const;

    void dealRule(const string &rule);
    void dealFile(const string &filename);
    const string &transform(const string &s);
private:
    std::unordered_map<string, int> _file;
    std::map<string, string> _rule;
};

};

#endif
