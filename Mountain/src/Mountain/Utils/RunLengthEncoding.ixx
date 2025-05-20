export module Mountain:Utils_RunLengthEncoding;

import "Mountain/Core.hpp";

import std;

export namespace Mountain
{
    class RunLengthEncoding
    {
    public:
        static std::string Encode(const std::string& str);
        static std::string Decode(const std::string& data);
    };
}
