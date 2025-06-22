#include <iostream>

using std::cout;
using std::endl;

class SafeFile
{
public:
    SafeFile(FILE *fp)
    :_fp(fp)
    {
        cout << "SafeFile(FILE*)" << endl;
        if (nullptr == _fp) {
            cout << "_fp == nullptr" << endl;
        }
    }

    ~SafeFile()
    {
        cout << "~SafeFile()" << endl;
        if (_fp) {
            fclose(_fp);
            cout << "fclose(_fp)" << endl;
        }
    }
private:
    FILE *_fp;
};

int main()
{
    SafeFile sf(fopen("1.txt", "w"));
    return 0;
}

