#include <iostream>

using std::cout;
using std::endl;

template<typename T>
class RAII
{
public:
    RAII(T *data)
    :_data(data)
    {
        cout << "RAII(T*)" << endl;
    }
    ~RAII()
    {
        cout << "~RAII()" << endl;
        if (_data) {
            delete _data;
            _data = nullptr;
        }
    }

    T *operator->() 
    {
        return _data;
    }

    T &operator*() 
    {
        return *_data;
    }

    T *get() 
    {
        return _data;
    }

    void reset(T *data) 
    {
        if (_data) {
            delete _data;
            _data = nullptr;
        }
        _data = data;
    }
private:
    T *_data;
};

int main()
{
    return 0;
}

