#pragma once

#include "Mountain/core.hpp"

#include <string>

BEGIN_MOUNTAIN

class RunLengthEncoding
{
public:
    static std::string Encode(const std::string& str);
    static std::string Decode(const std::string& data);
};

END_MOUNTAIN
