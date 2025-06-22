#include <iostream>

using std::cout;
using std::endl;

class Data
{
public:
    Data(int data = 10)
    : _data(data)
    {
        cout << "Data(int = 10)" << endl;
    }
    int getData()
    {
        return _data;
    }
    ~Data()
    {
        cout << "~Data()" << endl;
    }
private:
    int _data;
};

class SecondLayer
{
public:
    SecondLayer(Data *pdata)
    : _pdata(pdata)
    {
        cout << "SecondLayer(Data *)" << endl;
    }

    Data *operator->()
    {
        return _pdata;
    }

    Data &operator*()
    {
        return *_pdata;
    }

    ~SecondLayer()
    {
        cout << "~SecondLayer()" << endl;
        if(_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
    }
private:
    Data *_pdata;
};

class ThirdLayer
{
public:
    ThirdLayer(SecondLayer *sl)
    : _sl(sl)
    {
        cout << "ThirdLayer(Second *)" << endl;
    }

    SecondLayer &operator->()
    {
        return *_sl;
    }

    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;
        if(_sl)
        {
            delete _sl;
            _sl = nullptr;
        }
    }
private:
    SecondLayer *_sl;
};

int main()
{
#if 0
    SecondLayer sl(new Data());//栈对象
    /* sl.operator->()->getData(); */
    cout << "sl->getData() = " << sl->getData() << endl;
    /* sl.operator*().getData(); */
    cout << "(*sl).getData() = " << (*sl).getData() << endl;
#endif

    cout << endl;
    ThirdLayer tl(new SecondLayer(new Data(20)));
    /* tl.operator->().operator->()->getData(); */
    cout << "tl->getData() = " << tl->getData() << endl;
    return 0;
}
