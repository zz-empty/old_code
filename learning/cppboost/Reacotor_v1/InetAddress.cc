#include "InetAddress.hpp"


#include <string.h>
#include <arpa/inet.h>
#include <string>


using std::string;

namespace wd
{

InetAddress::InetAddress(const unsigned short port, const string &ip)
{
    ::memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
:_addr(addr)
{}

string InetAddress::ip() const
{
    return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const
{
    return ntohs(_addr.sin_port);
}

}//end of namespace wd
