#pragma once

#include <exception>
#include <string>

#include "Mountain/Core.hpp"

namespace Mountain
{
    class Exception : public std::exception
    {
    public:
        using std::exception::exception;

        [[nodiscard]]
        const char_t* GetMessage() const;
    };
}
