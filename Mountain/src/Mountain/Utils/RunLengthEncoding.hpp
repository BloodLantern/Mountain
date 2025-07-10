#pragma once

#include "Mountain/Core.hpp"

#include <string>

namespace Mountain
{
    class RunLengthEncoding
    {
    public:
        ATTRIBUTE_NODISCARD
        static std::string Encode(const std::string& str);
        ATTRIBUTE_NODISCARD
        static std::string Decode(const std::string& data);
    };
}
