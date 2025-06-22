#include "TextQuery.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::stringstream;


namespace wd
{

QuaryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodate(new set<line_no>);

    auto loc = _word2number.find(sought);
    if (loc == _word2number.end()) {
        return QuaryResult(sought, nodate, _lines);
    }
    else {
        return QuaryResult(sought, loc->second, _lines);
    }

}


void TextQuery::handleLine(string &line)
{
    size_t i = 0;
    for (; i < line.size(); ++i) {
        if (line[i] >= 'a' && line[i] <= 'z') {
            continue;
        }
        else if (line[i] >= 'A' && line[i] <= 'Z') {
            line[i] += 32; 
        }
        else {
            line[i] = ' ';
        }
    }
}



TextQuery::TextQuery(const string &filename)
:_lines(new std::vector<string>)
{
    ifstream ifs(filename);
    if (!ifs.good()) {
        std::cerr << "The ifstream is not good!" << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {
        _lines->push_back(line);
        int no = _lines->size() - 1; //当前行号

        //处理每行中的非法数据
        handleLine(line);

        stringstream ss(line);
        string word;
        while (ss >> word) {
            if (word[0] >= 'a' && word[0] <= 'z') {
                auto &ret = _word2number[word];
                if (!ret) {
                    ret.reset(new set<line_no>); //如果单词第一次出现，分配一个新的set
                }
               _word2number[word]->insert(no); 
            }
        }
    }

    //close ifstream
    ifs.close();
}


std::ostream& print(std::ostream &os, const QuaryResult &rhs)
{
    string time = rhs._lineno->size() ? "times" : "time";
    os << rhs._sought << " occurs " << rhs._lineno->size() << " " << time <<  endl;
    
    for (auto num : *rhs._lineno) {
        os << "\t(line " << num + 1 << ")\t\b\b" 
           << *(rhs._lines->begin() + num) << endl;
    }
    return os;
}


}//end of namespace wd
