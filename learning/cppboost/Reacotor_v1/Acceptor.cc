#include "Acceptor.hpp"

namespace wd
{

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}


void Acceptor::setReuseAddr()
{
    int on = 1;
    if (setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        ::perror("setsockopt");
    }
}

void Acceptor::setReusePort()
{
    int on = 1;
    if (setsockopt(fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) < 0) {
        ::perror("setsockopt");
    }
}

void Acceptor::bind()
{
    if (::bind(fd(), (struct sockaddr*)_addr.getInetAddressPtr(), sizeof(_addr)) < 0) {
        ::perror("bind");
    }
}

void Acceptor::listen()
{
    ::listen(fd(), 128);
}

int Acceptor::accept()
{
    int peerfd = ::accept(fd(), nullptr, nullptr);
    if (peerfd < 0) {
        ::perror("peerfd");
    }
    return peerfd;
}

}//end of namespace wd
