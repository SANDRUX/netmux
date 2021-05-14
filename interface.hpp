#pragma once

#include <iostream>
#include <vector>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

namespace netmux
{
    enum {LISTENER, CLIENT};

    class socket
    {
    protected:
        int sfd;

    public:
        virtual bool send(const std::vector<uint8_t> &) = 0;
        virtual bool receive(std::vector<uint8_t> &) = 0;
        virtual ~socket() = 0;
    };

    class TcpSocket final : public socket
    {
    public:
        TcpSocket (const int);
        TcpSocket (const TcpSocket &);
        bool operator=(const TcpSocket &);
        bool send(const std::vector<uint8_t> &) const;
        bool receive(std::vector<uint8_t> &) const;
        ~TcpSocket();
    };
}
