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

Color Calc::Lerp(const Color& value, const Color& target, const float_t time)
{
    const Vector4 v = static_cast<Vector4>(value);
    const Vector4 t = static_cast<Vector4>(target);

    Vector4 result = Lerp(v * v, t * t, time);

    result.x = std::sqrt(result.x);
    result.y = std::sqrt(result.y);
    result.z = std::sqrt(result.z);
    result.w = std::sqrt(result.w);
    
    return Color(result);
}

Color Calc::Lerp(const Color& value, const Color& target, const float_t time, const Easing::Easer easer)
{
    const Vector4 v = static_cast<Vector4>(value);
    const Vector4 t = static_cast<Vector4>(target);

    Vector4 result = Lerp(v * v, t * t, time, easer);

    result.x = std::sqrt(result.x);
    result.y = std::sqrt(result.y);
    result.z = std::sqrt(result.z);
    result.w = std::sqrt(result.w);
    
    return Color(result);
}
