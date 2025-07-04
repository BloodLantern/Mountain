#pragma once

#include "Mountain/Core.hpp"

#include <string>

namespace Mountain
{
    class RunLengthEncoding
    {
    public:
        static std::string Encode(const std::string& str);
        static std::string Decode(const std::string& data);
    };
}
