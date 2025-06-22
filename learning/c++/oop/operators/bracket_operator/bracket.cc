#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class CharArray
{
public:
    CharArray(size_t sz = 10);
    ~CharArray();
    /* void display(); */

    char &operator[](size_t idx);
    size_t getSize();
private:
    size_t _size;
    char *_data;
};

size_t CharArray::getSize()
{
    return _size;
}

//奇怪，用成员函数打印不出来_data[0]
#if 0
void CharArray::display()
{
    if (_size) {
        size_t idx = 0;
        for (idx = 0; idx < _size; ++idx) {
            cout << "idx = " << idx << ", _data[idx] = "<< _data[idx] << endl;
        }
        cout << endl;
    }
}
#endif

CharArray::CharArray(size_t sz) 
:_size(sz)
,_data(new char[_size + 1]())
{
    cout << "CharArray(size_t = 10)" << endl;
}
CharArray::~CharArray()
{
    cout << "~CharArray()" << endl;
    if (_data) {
        delete [] _data;
        _data = nullptr;
    }
}
char &CharArray::operator[](size_t idx)
{
    if (0 < idx) {
        return _data[idx];
    }
    else {
        static char nullChar = '\0';
        return nullChar;
    }
}

int main()
{
    const char *ptr = "helloworld";
    CharArray ca(strlen(ptr) + 1);
    
    //init ca
    size_t idx = 0;
    for (idx = 0; idx < ca.getSize(); ++idx) {
        ca[idx] = ptr[idx];
        cout << "idx = " << idx << ", ca[idx] = " << ca[idx] << endl;
    }

    for (idx = 0; idx < ca.getSize(); ++idx) {
        cout << ca[idx] << " ";
    }
    cout << endl;

    return 0;
}

