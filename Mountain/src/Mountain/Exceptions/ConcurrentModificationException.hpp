#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"

namespace Mountain
{
    class ConcurrentModificationException : public Exception
    {
    public:
        static constexpr const char_t* Message = "The container has been modified while iterating over it.";

        ConcurrentModificationException();
    };
}
