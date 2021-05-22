#include "socket_interface.hpp"
#include "exception.hpp"

#define BACKLOG 2048

netmux::TcpListener::TcpListener(const int port) : socket(TCP)
{
    sockaddr_in * addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;

    if (::bind(this->sfd, (sockaddr *)addr, sizeof(sockaddr)) == -1)
    {
        throw exception("Error caught when binding a socket!");
    }

    if (::listen(this->sfd, BACKLOG) == -1)
    {
        throw exception("Error caught when setting socket as listener!");
    }
}

netmux::TcpListener::TcpListener(const socket & obj) : socket(obj)
{
}

bool netmux::TcpListener::operator = (const socket & obj)
{
    if (this->sfd != -1)
    {
        if (close(this->sfd) == -1)
        {
            throw exception("Could not close the socket, Error occurred or already closed!");
        }
    }
    this->sfd = obj.get_fd();
}

bool netmux::TcpListener::accept()
{
    this->cfd.push_back(::accept(this->sfd, NULL, NULL));

    if (this->cfd[cfd.size()] == -1)
    {
        return false;
    }

    return true;
}

netmux::TcpListener::~TcpListener()
{
    if (this->sfd != -1)
    {
        if (close(this->sfd) == -1)
        {
            std::cerr << "Could not close the socket, Error occurred or already closed!";
        }
    }
}