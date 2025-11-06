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

int8_t Random::SByte(const int8_t minInclusive, const int8_t maxExclusive)
{
    return static_cast<int8_t>(Short(minInclusive, maxExclusive));
}

uint8_t Random::Byte(const uint8_t minInclusive, const uint8_t maxExclusive)
{
    return static_cast<uint8_t>(Short(minInclusive, maxExclusive));
}

int16_t Random::Short(const int16_t minInclusive, const int16_t maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, static_cast<int16_t>(maxExclusive - 1)};
    return dist(m_Engine);
}

uint16_t Random::UShort(const uint16_t minInclusive, const uint16_t maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, static_cast<uint16_t>(maxExclusive - 1)};
    return dist(m_Engine);
}

int32_t Random::Int(const int32_t minInclusive, const int32_t maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

uint32_t Random::UInt(const uint32_t minInclusive, const uint32_t maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

int64_t Random::Long(const int64_t minInclusive, const int64_t maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

uint64_t Random::ULong(const uint64_t minInclusive, const uint64_t maxExclusive)
{
    std::uniform_int_distribution dist{minInclusive, maxExclusive - 1};
    return dist(m_Engine);
}

float_t Random::Float(const float_t minInclusive, const float_t maxExclusive)
{
    std::uniform_real_distribution dist{minInclusive, maxExclusive};
    return dist(m_Engine);
}

double_t Random::Double(const double_t minInclusive, const double_t maxExclusive)
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

bool_t Random::Chance(const float_t probability)
{
    std::bernoulli_distribution dist{probability};
    return dist(m_Engine);
}

Vector2 Random::PointInCircle(const Vector2& center, const float_t radius)
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
    const float_t angle = Float(0.f, Calc::TwoPi);
    return { std::cos(angle), std::sin(angle) };
}
