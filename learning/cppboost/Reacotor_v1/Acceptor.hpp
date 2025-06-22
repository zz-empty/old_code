#ifndef __ACCEPTOR_HPP__
#define __ACCEPTOR_HPP__

#include "Socket.hpp"
#include "InetAddress.hpp"

#include <string>

using std::string;

namespace wd
{

class Acceptor
{
public:
    Acceptor(unsigned short port, const string & ip = "127.0.0.1")
    :_listensock()
    ,_addr(port, ip)
    {}

    void ready();
    int accept();
    int fd() const { return _listensock.fd(); }
private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();

private:
    Socket _listensock;
    InetAddress _addr;
};

}//end of namespace wd

#endif
