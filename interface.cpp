#include "interface.hpp"
#include "exception.hpp"

netmux::TcpClient::TcpClient ()
{
    this->sfd = ::socket(AF_INET, SOCK_STREAM, 0);

    if (this->sfd == -1)
    {
        throw exception("Error caught when creating a tcp socket!");
    }
}

netmux::TcpClient::TcpClient (const TcpClient & obj)
{
    this->sfd = obj.sfd;
}

void netmux::TcpClient::operator = (const TcpClient & obj)
{
    this->sfd = obj.sfd;
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

size_t netmux::TcpClient::send (const std::vector<uint8_t> & buf) const
{
    size_t numWrite = write(this->sfd, buf.data(), sizeof(decltype(buf[0])) * buf.size());

    if (numWrite == -1)
    {
        return -1;
    }

    return numWrite;
}

size_t netmux::TcpClient::receive (std::vector<uint8_t> & buf) const
{
    buf.clear();
}

netmux::TcpClient::~TcpClient ()
{
    if (close(this->sfd) == -1)
    {
        std::cerr << "Could not close the socket, Error occurred or already closed!";
    }
}