# ifndef __SINGLETON_H__
# define __SINGLETON_H__

# include <stdlib.h>


//将Singleton声明为类模板
template<typename T>
class Singleton
{
public:
    //getInstance可能要接收多个参数，所以使用可变模板参数
    template<typename...Args>
        static T *getInstance(Args... args);
    static void destroy();
private:
    Singleton() = default;
    ~Singleton() = default;
    static T *_pInstance;//Singleton类中真正起着作用的是_pInstance这个指针，只需要将指针类型转换为模板型即可。
};

template<typename T>//类模板声明
template<typename...Args>//函数模板声明
T* Singleton<T>::getInstance(Args... args)
{
    //此处没有锁，如果采用饱汉模式，在多线程环境下，不安全
    if (nullptr == _pInstance) {
        atexit(destroy);
        _pInstance = new T(args...);//将接收到的参数包传递给new表达式，new表达式会将参数包又传递给T的构造函数
    }
    return _pInstance;
}

template <typename T>
void Singleton<T>::destroy()
{
    if (_pInstance) {
        delete _pInstance;
        _pInstance = nullptr;
    }
}
#endif

