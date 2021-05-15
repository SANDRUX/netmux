#include "socket_interface.hpp"
#include "exception.hpp"

netmux::TcpClient::TcpClient (const socket & obj)
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

void netmux::TcpClient::operator = (const socket & obj)
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

bool netmux::TcpClient::connect (const std::string & ip, const int port) const
{
    sockaddr_in * addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    inet_aton(ip.c_str(), &addr->sin_addr);
    
    int status = ::connect(this->sfd, (struct sockaddr *)addr, sizeof(sockaddr));

    if (status == -1)
    {
        return false;
    }

    return true;
}

netmux::TcpClient::~TcpClient ()
{
    if (this->sfd != -1)
    {
        if (close(this->sfd) == -1)
        {
            std::cerr << "Could not close the socket, Error occurred or already closed!";
        }
    }
}