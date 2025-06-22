#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include "Noncopyable.hpp"

namespace wd
{

class Socket : Noncopyable
{
public:
    Socket();
    ~Socket();
    explicit Socket(int fd);
    
    int fd() const { return _fd; };
    void shutdownWrite();

    void setNonblock();
private:
    int _fd;
};

}//end of namespace wd

#endif
