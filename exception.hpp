#pragma once

#include <iostream>
#include <exception>

namespace netmux
{
    class exception : public std::exception
    {
    private:
        std::string m_error{};

    public:
        exception(std::string error) : m_error{error} {}
        const char *what() const noexcept override { return this->m_error.c_str(); }
    };
}

