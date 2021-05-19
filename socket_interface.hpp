#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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
        enum
        {
            TCP,
            UDP
        };
        static std::unordered_map <int, int> ref_count;

    public:
        socket();
        socket(const int mode);
        socket(const socket &);
        virtual bool operator = (const socket &);
        virtual size_t send (const std::vector<uint8_t> &) const;
        virtual size_t receive (std::vector<uint8_t> &) const;
        inline int get_fd() const { return this->sfd; }
        virtual ~socket () = 0;
    };

    class TcpClient : public socket
    {
    public:
        TcpClient () : socket(TCP) {}
        TcpClient (const socket &);
        virtual bool operator = (const socket &) override;
        virtual bool connect (const std::string &, const int) const;
        virtual ~TcpClient ();
    };

    class TcpListener : public socket
    {
    private:
        int port;
        std::vector<int> cfd;
    public:
        TcpListener (const int);
        TcpListener (const socket &);
        virtual bool operator = (const socket &);
        virtual bool accept();
        inline const std::vector<int> & get_cfd() const { return this->cfd; }
        virtual ~TcpListener();
    };
}