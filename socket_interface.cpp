#include "socket_interface.hpp"
#include "exception.hpp"

netmux::socket::socket () : sfd(-1) 
{
}

netmux::socket::socket (const int mode)
{
    if (mode == TCP)
    {
        this->sfd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (this->sfd == -1)
        {
            throw exception("Error caught when creating a tcp socket!");
        }
    }

    else if (mode == UDP)
    {
        this->sfd = ::socket(AF_INET, SOCK_DGRAM, 0);

        if (this->sfd == -1)
        {
            throw exception("Error caught when creating an udp socket!");
        }
    }

    this->ref_count[this->sfd] = 1;
}

netmux::socket::socket(const socket & obj)
{
    this->ref_count[obj.sfd] += 1;
    this->sfd = obj.sfd;
}

bool netmux::socket::operator = (const socket & obj)
{
    if (this->sfd == obj.sfd)
    {
        return true;
    }
    
    if (--(this->ref_count[this->sfd]) == 0)
    {
        if (close(this->sfd) == -1)
        {
            return false;
        }
    }

    this->sfd = obj.get_fd();
    this->ref_count[obj.sfd] += 1;
}

size_t netmux::socket::send (const std::vector<uint8_t> & buf) const
{
    size_t numWrite = write(this->sfd, buf.data(), sizeof(decltype(buf[0])) * buf.size());

    if (numWrite == -1)
    {
        return -1;
    }

    return numWrite;
}

size_t netmux::socket::receive (std::vector<uint8_t> & buf) const
{
    size_t size = sizeof(decltype(buf[0])) * buf.size();

    uint8_t data[size];

    size_t numRead = read(this->sfd, data, size);

    if (numRead == -1)
    {
        return -1;
    }

    buf.insert(buf.begin(), data, (data + size));

    return numRead;
}