#include "TextQuery.hpp"
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


void TextQuery::splitStringIntoDict(const string &input, size_t idx, char delimiter)
{
    string item;
    std::stringstream ss(input);

    while (getline(ss, item, delimiter)) {
        if (item[0] < 'a' || item[0] > 'z') {
        }
        else {
            _word2number[item].insert(idx);
            ++_dict[item];
        }
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

void TextQuery::addDict(ifstream &ifs)
{
    string line;
    size_t idx = 0;
    while (getline(ifs, line)) {
        //get per line from ifs
        _lines.push_back(line);

        handleLine(line);

        splitStringIntoDict(line, idx, ' ');
        ++idx;
    }
}


void TextQuery::read(const string &filename)
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

void TextQuery::store(const string &filename)
{
    std::ofstream ofs(filename);
    if (!ofs.good()) {
        std::cerr << "The ofstream is not good!" << endl;
    }

    for (auto &elem : _dict) {
        ofs << elem.first<< "\t" << elem.second << endl;
    }

    ofs.close();
}


void TextQuery::display() const
{
    for (auto &elem : _dict) {
        cout << elem.first << "\t" << elem.second << endl;
    }
}

void TextQuery::top10()
{
    //multimap 的key是词频
    std::multimap<int,string, std::greater<int>> map_cnt;

    for (auto &elem : _dict) {
        map_cnt.insert({elem.second, elem.first});
    }

    auto it = map_cnt.begin();
    int idx = 0;
    for (; idx < 10; ++idx, ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
}

void TextQuery::query(const string &word)
{
    //display word_cnt and per word_line
    auto ret = _word2number.find(word);
    if (ret == _word2number.end()) {
        cout << "Not find!" << endl;
    }
    else {
        cout << word << " occurs " << _dict[word] << " times." << endl;
        cout << "_dict[] = " << _dict[word] << endl;
        //print word's line
        for (auto &num : _word2number[word]) {
            cout << "\t(line " << num + 1 << ") ";
            cout << _lines[num] << endl;
        }
    }
}

}//end of namespace wd
