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


void Dictionary::splitLineIntoDict(const string &input, char delimiter)
{
    string item;
    std::stringstream ss(input);

    while (getline(ss, item, delimiter)) {
        if (item[0] < 'a' || item[0] > 'z') {
            //去掉空字符
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
        //处理每一行的非法数据，再将这一行中的单词存入词典
        handleLine(line);
        splitLineIntoDict(line, ' ');
    }
}


Dictionary::Dictionary(const string &filename)
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
    //词频可能重复，用multimap存储
    std::multimap<int, string, std::greater<int>> map_cnt;

    for (auto &elem : _dict) {
        map_cnt.insert({elem.second, elem.first});
    }


    //打印词频前10的单词
    auto it = map_cnt.begin();
    int idx = 0;
    for (; idx < 10; ++idx, ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
}


}//end of namespace wd
