#include "Mountain/utils/color.hpp"

using namespace Mountain;

uint32_t Color::GetPackedValue() const
{
    const uint8_t byteR = static_cast<uint8_t>(std::round(r * std::numeric_limits<uint8_t>::max()));
    const uint8_t byteG = static_cast<uint8_t>(std::round(g * std::numeric_limits<uint8_t>::max()));
    const uint8_t byteB = static_cast<uint8_t>(std::round(b * std::numeric_limits<uint8_t>::max()));
    const uint8_t byteA = static_cast<uint8_t>(std::round(a * std::numeric_limits<uint8_t>::max()));

    return byteA << 24 | byteB << 16 | byteG << 8 | byteR;
}
