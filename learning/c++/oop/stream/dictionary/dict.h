#ifndef __DICT_H__
#define __DICT_H__

#include <string>
#include <vector>

//this DS record  word_name and word_count
struct Record
{
    Record(const std::string word, int cnt);
    Record(const Record &rhs);

    std::string _word;
    int _frequency;
};

class Dictionary
{
public:
    Dictionary(int capa = 100);

    void read(const std::string &filename);
    void store(const std::string &filename);
    void display();
    void sort();
    void cnt_sort();

    int isOldWord(const std::string &word);
private:
    std::vector<Record> _dict;
};



#endif
