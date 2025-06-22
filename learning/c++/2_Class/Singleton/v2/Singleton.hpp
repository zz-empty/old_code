#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__


namespace wd
{

class Singleton
{
public:
    static Singleton* getInstance();
    static void destroy();

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    class AutoRelease
    {
    public:
        AutoRelease();
        ~AutoRelease();
    };

    static Singleton *_pOnly;
    static AutoRelease _auto;
};


}// end of namespace wd

#endif
