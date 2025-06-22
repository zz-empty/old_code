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


void Dictionary::splitStringIntoDict(const string &input, char delimiter)
{
    string item;
    std::stringstream ss(input);

    while (getline(ss, item, delimiter)) {
        if (item[0] < 'a' || item[0] > 'z') {
        }
        else {
            ++_dict[item];
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
        ofs << elem.first<< "\t" << elem.second << endl;
    }

    ofs.close();
}


void Dictionary::display() const
{
    for (auto &elem : _dict) {
        cout << elem.first << "\t" << elem.second << endl;
    }
}

void Dictionary::top10()
{
    std::multimap<int,string, std::greater<int>> map_cnt;

    for (auto &elem : _dict) {
        map_cnt.insert({elem.second, elem.first});
    }

    /* _dict.clear(); */

    auto it = map_cnt.begin();
    int idx = 0;
    for (; idx < 10; ++idx, ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
}


}//end of namespace wd
