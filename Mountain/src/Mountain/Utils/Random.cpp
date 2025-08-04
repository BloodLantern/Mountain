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

int8_t Random::SByte(const int8_t min, const int8_t max)
{
    return static_cast<int8_t>(Short(min, max));
}

uint8_t Random::Byte(const uint8_t min, const uint8_t max)
{
    return static_cast<uint8_t>(Short(min, max));
}

int16_t Random::Short(const int16_t min, const int16_t max)
{
    std::uniform_int_distribution dist{min, max};
    return dist(m_Engine);
}

uint16_t Random::UShort(const uint16_t min, const uint16_t max)
{
    std::uniform_int_distribution dist{min, max};
    return dist(m_Engine);
}

int32_t Random::Int(const int32_t min, const int32_t max)
{
    std::uniform_int_distribution dist{min, max};
    return dist(m_Engine);
}

uint32_t Random::UInt(const uint32_t min, const uint32_t max)
{
    std::uniform_int_distribution dist{min, max};
    return dist(m_Engine);
}

int64_t Random::Long(const int64_t min, const int64_t max)
{
    std::uniform_int_distribution dist{min, max};
    return dist(m_Engine);
}

uint64_t Random::ULong(const uint64_t min, const uint64_t max)
{
    std::uniform_int_distribution dist{min, max};
    return dist(m_Engine);
}

float_t Random::Float(const float_t min, const float_t max)
{
    std::uniform_real_distribution dist{min, max};
    return dist(m_Engine);
}

double_t Random::Double(const double_t min, const double_t max)
{
    std::uniform_real_distribution dist{min, max};
    return dist(m_Engine);
}

Color Random::Color(const Mountain::Color minValues, const Mountain::Color maxValues)
{
    return Mountain::Color{
        Float(minValues.r, maxValues.r),
        Float(minValues.g, maxValues.g),
        Float(minValues.b, maxValues.b),
        Float(minValues.a, maxValues.a)
    };
}

ColorHsva Random::ColorHsva(const Mountain::ColorHsva minValues, const Mountain::ColorHsva maxValues)
{
    return Mountain::ColorHsva{
        Float(minValues.h, maxValues.h),
        Float(minValues.s, maxValues.s),
        Float(minValues.v, maxValues.v),
        Float(minValues.a, maxValues.a)
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
