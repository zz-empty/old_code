#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;

namespace  wd
{

struct Record
{
    Record(const string &name, int cnt)
    :word_name(name)
    ,word_cnt(cnt)
    {}

    string word_name;
    int word_cnt;
};


class Dictionary
{
public:
    Dictionary() {  _dict.reserve(200);  }

    void read(const string &filename);
    void store(const string &filename);
    void display() const;

    //handle readfile
    void addDict(ifstream &ifs);
    void handleLine(string &line);
    void splitStringIntoDict(const string &input, char delimiter = ' ');

    //sort dict
    void sort_by_wordcnt();
    void sort_by_name();

    //print top10
    void top10();

private:
    vector<Record> _dict;
};


}//end of namespace wd

#endif
