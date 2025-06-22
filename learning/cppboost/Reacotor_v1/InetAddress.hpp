#ifndef __INETADDRESS_HPP__
#define __INETADDRESS_HPP__

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

using std::string;

namespace wd
{

class InetAddress
{
public:
    InetAddress(const unsigned short port, const string &ip);
    InetAddress(const struct sockaddr_in &addr);
    string ip() const;
    unsigned short port() const;

    struct sockaddr_in * getInetAddressPtr() { return &_addr; }
private:
    struct sockaddr_in _addr;
};

}//end of namespace wd

#endif
