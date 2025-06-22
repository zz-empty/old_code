#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__


namespace wd
{

class AutoRelease
{
public:
    ~AutoRelease();
};

class Singleton
{
    friend class AutoRelease;
public:
    static Singleton* getInstance();
    static void destroy();

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    static Singleton *_pOnly;
};


}// end of namespace wd

#endif
