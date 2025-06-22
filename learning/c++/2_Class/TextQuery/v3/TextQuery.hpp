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


class QueryResult;

//用来存储文件的类
class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(const string &filename);
    QueryResult query(const string &sought) const;

    void handleLine(string &line);

private:
    shared_ptr<vector<string>> _lines;
    map<string, shared_ptr<set<line_no>>> _word2number;
    /* map<string, size_t> _dict; */
};

//用来返回查询结果的类
class QueryResult
{
    friend std::ostream& print(std::ostream &os, const QueryResult &rhs);
public:
    using line_no = TextQuery::line_no;

    QueryResult(string s, shared_ptr<set<line_no>> no, shared_ptr<vector<string>> lines)
    :_sought(s)
    ,_lineno(no)
    ,_lines(lines)
    {}

    set<line_no>::iterator begin() 
    {   return _lineno->begin();    }

    set<line_no>::iterator end()
    {   return _lineno->end();      }

    auto get_lines()
    {   return _lines;  }

private:
    string _sought; //查询单词
    shared_ptr<set<line_no>> _lineno;   //行号
    shared_ptr<vector<string>> _lines; //文件中的每一行
};



}//end of namespace wd

#endif
