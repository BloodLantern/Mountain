#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/Random.hpp"

using namespace Mountain;

Random Random::instance;

Random& Random::Instance() { return instance; }

Random::Random()
    : m_Engine{device()}
{
}

Random::Random(const std::default_random_engine::result_type seed)
    : m_Engine{seed}
{
}

s8 Random::SByte(const s8 minInclusive, const s8 maxExclusive)
{
    return static_cast<s8>(Short(minInclusive, maxExclusive));
}

u8 Random::Byte(const u8 minInclusive, const u8 maxExclusive)
{
    return static_cast<u8>(Short(minInclusive, maxExclusive));
}

s16 Random::Short(const s16 minInclusive, const s16 maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, static_cast<s16>(maxExclusive - 1)};
    return dist(m_Engine);
}

u16 Random::UShort(const u16 minInclusive, const u16 maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, static_cast<u16>(maxExclusive - 1)};
    return dist(m_Engine);
}

s32 Random::Int(const s32 minInclusive, const s32 maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

u32 Random::UInt(const u32 minInclusive, const u32 maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

s64 Random::Long(const s64 minInclusive, const s64 maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

u64 Random::ULong(const u64 minInclusive, const u64 maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

f32 Random::Float(const f32 minInclusive, const f32 maxExclusive)
{
    std::uniform_real_distribution dist{minInclusive, maxExclusive};
    return dist(m_Engine);
}

f64 Random::Double(const f64 minInclusive, const f64 maxExclusive)
{
    std::uniform_real_distribution dist{minInclusive, maxExclusive};
    return dist(m_Engine);
}

Color Random::Color(const Mountain::Color minValuesInclusive, const Mountain::Color maxValuesInclusive)
{
    return Mountain::Color{
        Float(minValuesInclusive.r, maxValuesInclusive.r),
        Float(minValuesInclusive.g, maxValuesInclusive.g),
        Float(minValuesInclusive.b, maxValuesInclusive.b),
        Float(minValuesInclusive.a, maxValuesInclusive.a)
    };
}

ColorHsva Random::ColorHsva(const Mountain::ColorHsva minValuesInclusive, const Mountain::ColorHsva maxValuesInclusive)
{
    return Mountain::ColorHsva{
        Float(minValuesInclusive.h, maxValuesInclusive.h),
        Float(minValuesInclusive.s, maxValuesInclusive.s),
        Float(minValuesInclusive.v, maxValuesInclusive.v),
        Float(minValuesInclusive.a, maxValuesInclusive.a)
    };
}

bool Random::Chance(const f32 probability)
{
    std::bernoulli_distribution dist{probability};
    return dist(m_Engine);
}

Vector2 Random::PointInCircle(const Vector2& center, const f32 radius)
{
    // See https://youtu.be/4y_nmpv-9lI
    while (true)
    {
        const Vector2 point = PointInRectangle(Vector2::One() * -1.f, Vector2::One() * 2.f);
        if (point.SquaredLength() < 1.f)
            return center + point * radius;
    }
}

Vector2 Random::PointInRectangle(const Vector2& position, const Vector2& size)
{
    return { Float(position.x, position.x + size.x), Float(position.y, position.y + size.y) };
}

Vector2 Random::Direction()
{
    const f32 angle = Float(0.f, Calc::TwoPi);
    return { std::cos(angle), std::sin(angle) };
}
