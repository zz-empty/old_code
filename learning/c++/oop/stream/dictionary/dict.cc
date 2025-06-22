#include "dict.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

Record::Record(const std::string word, int cnt)
:_word(word)
,_frequency(cnt)
{
}

Record::Record(const Record &rhs)
{
    _word = rhs._word;
    _frequency = rhs._frequency;
}

Dictionary::Dictionary(int capa)
{
    _dict.reserve(capa);
}


void Dictionary::read(const std::string &filename)
{
    //create ifstream and check
    std::ifstream ifs(filename);
    if (ifs) {
        std::cerr << "open " << filename << " error!" << endl;
        return;
    }

    /* size_t exit = 0;//control while exit, test low data_volume */
    size_t word_cnt = 0;//count words

    //deal per line
    string line;
    while (getline(ifs, line)) {
        
        //deal every char of line
        size_t idx = 0;
        for (idx = 0; idx < line.size(); ++idx) {
            if (line[idx] >= 'A' && line[idx] <= 'Z') {
                line[idx] += 32;
            }
            else if (line[idx] >= 'a' && line[idx] <= 'z') {
            }
            else  {
                line[idx] = ' ';
            }
            
        }

        //extract word from string
        string word;
        for (idx = 0; idx < line.length(); ++idx) {
            if (line[idx] >= 'a' && line[idx] <= 'z') {
                word += line[idx];
                /* cout << "word = " << word << endl; */
            }
            else {
                if (word.length()) {
                    /* cout << "word_cnt:" << word_cnt << ", word = " << word << endl; */ 

                    //store into dictionary
#if 1
                    int idx = isOldWord(word);
                    if (-1 != idx) {
                        _dict[idx]._frequency++;
                        /* cout << "id=" << idx << ", word=" */
                        /*      << word << " ,frequency=" << _dict[idx]._frequency << endl; */
                    }
                    else {
                        /* Record rec(word, 1); */ 
                        _dict.push_back(Record(word, 1));
                        /* cout << "vectory size = " << _dict.size() << endl; */
                        /* cout << "id:" << word_cnt << ", word = " << _dict[word_cnt]._word << endl; */

                        ++word_cnt;
                    }
#endif
                    word.clear();
                }
            }
        }

        //exit
        /* ++exit; */
        /* if (50 == exit) { */
        /*     break; */
        /* } */
    }

    ifs.close();
}

int Dictionary::isOldWord(const string &word)
{
    /* cout << "----compare begin-----" << endl; */
    /* cout << "search word :" << word << endl; */
    size_t idx = 0;
    for (idx = 0; idx < _dict.size(); ++idx) {
        if (_dict[idx]._word == word) {
            /* cout << "Find! pos:" << idx << endl; */
            /* cout << "----compare end-----" << endl; */
            return idx;
        }
    }

    /* cout << "Not found! New word!" << endl; */
    /* cout << "----compare end-----" << endl; */

    //return pos
    return -1;
}

void Dictionary::display()
{
    size_t idx = 0;
    cout << endl;
    cout << "------Dictionary display------" << endl;
    for (idx = 0; idx < _dict.size(); ++idx) {
        cout << "idx:" << idx 
             << ", word = " << _dict[idx]._word 
             << ", cnt = " << _dict[idx]._frequency << endl; 
    }
}


bool mycompare(Record lhs, Record rhs)
{
    return lhs._word < rhs._word;
}
bool cntcompare(Record lhs, Record rhs)
{
    return lhs._frequency > rhs._frequency;
}

void Dictionary::sort()
{
    std::sort(_dict.begin(), _dict.end(), mycompare);
}

void Dictionary::cnt_sort()
{
    std::sort(_dict.begin(), _dict.end(), cntcompare);
}

void Dictionary::store(const std::string &filename)
{
    std::ofstream ofs(filename);
    if (!ofs.good()) {
        std::cerr << "The ofstream is bad!" << endl;
        return;
    }

    //put every Record to ofs
    size_t idx = 0;
    for (idx = 0; idx < _dict.size(); ++idx) {
        ofs << _dict[idx]._word << "\t" 
            << _dict[idx]._frequency << endl;
    }

    ofs.close();
}
