#ifndef __TEXTQUERY_HPP__
#define __TEXTQUERY_HPP__

#include <string>
#include <map>
#include <vector>
#include <set>
#include <memory>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::ifstream;
using std::shared_ptr;

namespace  wd
{

using line_no = vector<string>::size_type;
class QuaryResult;

class TextQuery
{
public:
    TextQuery(const string &filename);
    QuaryResult query(const string &sought) const;

    void handleLine(string &line);

private:
    shared_ptr<vector<string>> _lines;
    map<string, shared_ptr<set<line_no>>> _word2number;
    /* map<string, size_t> _dict; */
};

class QuaryResult
{
    friend std::ostream& print(std::ostream &os, const QuaryResult &rhs);
public:
    QuaryResult(string s, shared_ptr<set<line_no>> no, shared_ptr<vector<string>> lines)
    :_sought(s)
    ,_lineno(no)
    ,_lines(lines)
    {}

private:
    string _sought; //查询单词
    shared_ptr<set<line_no>> _lineno;   //行号
    shared_ptr<vector<string>> _lines; //文件中的每一行
};

}//end of namespace wd

#endif
