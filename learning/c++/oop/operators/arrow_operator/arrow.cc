#include <iostream>

using std::cout;
using std::endl;

class Data
{
public:
    Data(int data = 10) :_data(data)
    {
        cout << "Data(int = 10)" << endl;
    }
    ~Data()
    {
        cout << "~Data()" << endl;
    }
    int getData()
    {
        return _data;
    }
private:
    int _data;
};

class SecondLayer
{
public:
    SecondLayer(Data *pdata) :_pdata(pdata)
    {
        cout << "SecondLayer(Data*)" << endl;
    }
    ~SecondLayer()
    {
        cout << "~SecondLayer()" << endl;
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }
    Data *operator->()
    {
        return _pdata;
    }
private:
    Data *_pdata;
};

class ThirthLayer
{
public:
    ThirthLayer(SecondLayer *sl) :_sl(sl)
    {
        cout << "ThirthLayer(SecondLayer*)" << endl;
    }
    ~ThirthLayer()
    {
        cout << "~ThirthLayer()" << endl;
        if (_sl) {
            delete _sl;
            _sl = nullptr;
        }
    }
    SecondLayer &operator->()
    {
        return *_sl;
    }
private:
    SecondLayer *_sl;
};

int main()
{
    /* SecondLayer sl(new Data()); */
    /* cout << "sl->getData() = " << sl->getData() << endl; */

    cout << endl << endl;
    ThirthLayer tl(new SecondLayer(new Data(20)));
    cout << "tl->getData() = " << tl->getData() << endl;
    return 0;
}

