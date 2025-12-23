
#include "Mountain/Math/Easing.hpp"

#include "Mountain/Math/Calc.hpp"

f32 Easing::SineIn(const f32 t)
{
    return 1.f + std::sin(Calc::PiOver2 * (t - 1));
}

f32 Easing::SineOut(const f32 t)
{
    return std::sin(Calc::PiOver2 * t);
}

f32 Easing::SineInOut(const f32 t)
{
    return 0.5f * (1.f + std::sin(Calc::Pi * (t - 0.5f)));
}

f32 Easing::ExpoIn(const f32 t)
{
    return (std::pow(2.f, 8.f * t) - 1.f) / 255.f;
}

f32 Easing::ExpoOut(const f32 t)
{
    if (t <= 0.f)
        return 0.f;

    return t >= 1.f ? 1.f : 1.f - std::pow(2.f, -8.f * t);
}

f32 Easing::ExpoInOut(const f32 t)
{
    if (t == 0.f)
        return 0.f;
    if (t == 1.f)
        return 1.f;

    if (t < 0.5f)
        return (std::pow(2.f, 16.f * t) - 1.f) / 510.f;

    return 1.f - 0.5f * std::pow(2.f, -16.f * (t - 0.5f));
}

f32 Easing::CircIn(const f32 t)
{
    return 1.f - std::sqrt(1.f - t);
}

f32 Easing::CircOut(const f32 t)
{
    return std::sqrt(t);
}

f32 Easing::CircInOut(const f32 t)
{
    if (t < 0.5f)
        return (1.f - std::sqrt(1.f - 2.f * t)) * 0.5f;

    return (1.f + std::sqrt(2.f * t - 1.f)) * 0.5f;
}

f32 Easing::ElasticIn(const f32 t)
{
    const f32 t2 = t * t;
    return t2 * t2 * std::sin(t * Calc::Pi * 4.5f);
}

f32 Easing::ElasticOut(const f32 t)
{
    const f32 t2 = (t - 1.f) * (t - 1.f);
    return 1.f - t2 * t2 * std::cos(t * Calc::Pi * 4.5f);
}

f32 Easing::ElasticInOut(const f32 t)
{
    f32 t2;
    if (t < 0.45f)
    {
        t2 = t * t;
        return 8.f * t2 * t2 * std::sin(t * Calc::Pi * 9.f);
    }

    if (t < 0.55f)
        return 0.5f + 0.75f * std::sin(t * Calc::Pi * 4.f);

    t2 = (t - 1.f) * (t - 1.f);
    return 1.f - 8.f * t2 * t2 * std::sin(t * Calc::Pi * 9.f);
}

f32 Easing::BounceIn(const f32 t)
{
    return std::pow(2.f, 6.f * (t - 1.f)) * std::abs(std::sin(t * Calc::Pi * 3.5f));
}

f32 Easing::BounceOut(const f32 t)
{
    return 1.f - std::pow(2.f, -6.f * t) * std::abs(std::cos(t * Calc::Pi * 3.5f));
}

f32 Easing::BounceInOut(const f32 t)
{
    if (t < 0.5f)
        return 8.f * std::pow(2.f, 8.f * (t - 1.f)) * std::abs(std::sin(t * Calc::Pi * 7.f));

    return 1.f - 8.f * std::pow(2.f, -8.f * t) * std::abs(std::sin(t * Calc::Pi * 7.f));
}
