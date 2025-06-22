#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

#include <string>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;
using std::ifstream;

namespace  wd
{

#if 0
struct Record
{
    Record(const string &name, int cnt)
    :word_name(name)
    ,word_cnt(cnt)
    {}

    string word_name;
    int word_cnt;
};
#endif


class Dictionary
{
public:
    Dictionary() 
    {}

    void read(const string &filename);
    void store(const string &filename);
    void display() const;

    //handle readfile
    void addDict(ifstream &ifs);
    void handleLine(string &line);
    void splitStringIntoDict(const string &input, char delimiter = ' ');

    //sort dict
    /* void sort_by_wordcnt(); */

    //print top10
    void top10();

private:
    map<string, size_t> _dict;
};


}//end of namespace wd

#endif
