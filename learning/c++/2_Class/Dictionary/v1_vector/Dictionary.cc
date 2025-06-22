#include "Dictionary.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;


namespace wd
{

bool operator==(const Record &lhs, const Record &rhs)
{
    return lhs.word_name == rhs.word_name;
}

void Dictionary::splitStringIntoDict(const string &input, char delimiter)
{
    string item;
    std::stringstream ss(input);

    while (getline(ss, item, delimiter)) {
        if (item[0] < 'a' || item[0] > 'z') {
        }
        else {
            auto ret = std::find(_dict.begin(), _dict.end(), Record(item, 1));
            if (ret == _dict.end()) {
                //item is new word
                _dict.push_back(Record(item, 1));
            }
            else {
                ret->word_cnt++;
            }
        }
    }
}

void Dictionary::handleLine(string &line)
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
    /* cout << "handled_line = " << line << endl; */
}

void Dictionary::addDict(ifstream &ifs)
{
    //get per line from ifs
    string line;
    while (getline(ifs, line)) {
        handleLine(line);
        splitStringIntoDict(line, ' ');
    }
}


void Dictionary::read(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs.good()) {
        std::cerr << "The ifstream is not good!" << endl;
        return;
    }

    addDict(ifs);

    //close ifstream
    ifs.close();
}

void Dictionary::store(const string &filename)
{
    std::ofstream ofs(filename);
    if (!ofs.good()) {
        std::cerr << "The ofstream is not good!" << endl;
    }

    for (auto &elem : _dict) {
        ofs << elem.word_name << "\t" << elem.word_cnt << endl;
    }

    ofs.close();
}


void Dictionary::display() const
{
    for (auto &elem : _dict) {
        cout << elem.word_name << "\t" << elem.word_cnt << endl;
    }
}

void Dictionary::sort_by_wordcnt()
{
    std::multimap<int,string, std::greater<int>> map_cnt;

    for (auto &elem : _dict) {
        map_cnt.insert({elem.word_cnt, elem.word_name});
    }

    _dict.clear();
    for (auto &it : map_cnt) {
        _dict.push_back(Record(it.second, it.first));
    }
}

void Dictionary::sort_by_name()
{
    std::map<string, int> map_name;

    for (auto &elem : _dict) {
        map_name.insert({elem.word_name, elem.word_cnt});
    }

    _dict.clear();
    for (auto &it : map_name) {
        _dict.push_back(Record(it.first, it.second));
    }

}

void Dictionary::top10()
{
    sort_by_wordcnt();
    for (int i = 0; i < 10; ++i) {
        cout << _dict[i].word_name << "\t" << _dict[i].word_cnt << endl;
    }
}

}//end of namespace wd
