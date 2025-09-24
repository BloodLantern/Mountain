#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/Color.hpp"

using namespace Mountain;

Color::operator ImVec4() const { return ImVec4{ r, g, b, a }; }

std::string Color::ToString() const
{
    return std::format("{} ; {} ; {} ; {}", r, g, b, a);
}

std::string ColorHsva::ToString() const
{
    return std::format("{} ; {} ; {} ; {}", h, s, v, a);
}

Color Calc::Lerp(const Color& value, const Color& target, const float_t time)
{
    return Color{Lerp(value.ToVector4(), target.ToVector4(), time)};
}

Color Calc::Lerp(
    const Color& value,
    const Color& target,
    const float_t time,
    const Easing::Easer easer
)
{
    return Color{Lerp(value.ToVector4(), target.ToVector4(), time, easer)};
}

Color Calc::LerpFixed(const Color& value, const Color& target, const float_t time)
{
    const Vector4 v = value.ToVector4();
    const Vector4 t = target.ToVector4();

    Vector4 result = Lerp(v * v, t * t, time);

    result.x = std::sqrt(result.x);
    result.y = std::sqrt(result.y);
    result.z = std::sqrt(result.z);
    result.w = std::sqrt(result.w);

    return Color(result);
}

Color Calc::LerpFixed(const Color& value, const Color& target, const float_t time, const Easing::Easer easer)
{
    const Vector4 v = value.ToVector4();
    const Vector4 t = target.ToVector4();

    Vector4 result = Lerp(v * v, t * t, time, easer);

    result.x = std::sqrt(result.x);
    result.y = std::sqrt(result.y);
    result.z = std::sqrt(result.z);
    result.w = std::sqrt(result.w);

    return Color(result);
}
