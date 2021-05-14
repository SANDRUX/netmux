#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

namespace netmux
{
    class socket
    {
    protected:
        int sfd;

    public:
        virtual size_t send (const std::vector<uint8_t> &) const = 0;
        virtual size_t receive (std::vector<uint8_t> &) const = 0;
        virtual ~socket () = 0;
    };

    class TcpClient final : public socket
    {
    public:
        TcpClient ();
        TcpClient (const TcpClient &);
        void operator = (const TcpClient &);
        bool connect (const std::string &, const int) const;
        size_t send (const std::vector<uint8_t> &) const override;
        size_t receive (std::vector<uint8_t> &) const override;
        ~TcpClient ();
    };

    class TcpListener final : public socket
    {
        TcpListener ();
        TcpListener (const TcpListener &);
        bool operator = (const TcpListener &);
    };
}
