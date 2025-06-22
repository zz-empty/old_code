#ifndef __TEXTQUERY_HPP__
#define __TEXTQUERY_HPP__

#include <string>
#include <map>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::ifstream;

namespace  wd
{


class TextQuery
{
public:
    TextQuery() 
    {}

    void read(const string &filename);
    void store(const string &filename);
    void display() const;

    //handle readfile
    void addDict(ifstream &ifs);
    void handleLine(string &line);
    void splitStringIntoDict(const string &input, size_t idx, char delimiter = ' ');

    //print top10
    void top10();

    //query
    void query(const string &word);//耦合查询和打印

private:
    vector<string> _lines;
    map<string, set<int>> _word2number;
    map<string, size_t> _dict;
};


}//end of namespace wd

#endif
