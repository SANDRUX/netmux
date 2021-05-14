#include "interface.hpp"
#include "exception.hpp"

netmux::TcpSocket::TcpSocket (const int mode)
{
    if (mode == LISTENER)
    {
        this->sfd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (this->sfd == -1)
        {
            throw exception("Error caught when creating a tcp socket!");
        }
    }
}

netmux::TcpSocket::TcpSocket (const TcpSocket & obj)
{
    this->sfd = obj.sfd;
}

netmux::TcpSocket::~TcpSocket()
{
    if (close(this->sfd) == -1)
    {
        std::cerr << "Could not close the socket, Error occurred or already closed!";
    }
}