#include "Mountain/Utils/Color.hpp"

using namespace Mountain;

uint32_t Color::GetPackedValue() const
{
    const uint8_t byteR = static_cast<uint8_t>(Calc::Round(r * std::numeric_limits<uint8_t>::max()));
    const uint8_t byteG = static_cast<uint8_t>(Calc::Round(g * std::numeric_limits<uint8_t>::max()));
    const uint8_t byteB = static_cast<uint8_t>(Calc::Round(b * std::numeric_limits<uint8_t>::max()));
    const uint8_t byteA = static_cast<uint8_t>(Calc::Round(a * std::numeric_limits<uint8_t>::max()));

    return byteA << 24 | byteB << 16 | byteG << 8 | byteR;
}

Color::operator ImVec4() const { return ImVec4{ r, g, b, a }; }

Color Calc::Lerp(const Color& value, const Color& target, const float_t time)
{
    return Color{Lerp(static_cast<Vector4>(value), static_cast<Vector4>(target), time)};
}

Color Calc::Lerp(
    const Color& value,
    const Color& target,
    const float_t time,
    const Easing::Easer easer
)
{
    return Color{Lerp(static_cast<Vector4>(value), static_cast<Vector4>(target), time, easer)};
}

Color Calc::LerpFixed(const Color& value, const Color& target, const float_t time)
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

Color Calc::LerpFixed(const Color& value, const Color& target, const float_t time, const Easing::Easer easer)
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
