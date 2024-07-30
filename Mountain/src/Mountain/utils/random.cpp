#include "Mountain/utils/random.hpp"

#include <numbers>
#include <random>

std::random_device device;
std::mt19937 engine = std::mt19937(device());

using namespace Mountain;

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
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

uint16_t Random::UShort(const uint16_t min, const uint16_t max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

int32_t Random::Int(const int32_t min, const int32_t max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

uint32_t Random::UInt(const uint32_t min, const uint32_t max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

int64_t Random::Long(const int64_t min, const int64_t max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

uint64_t Random::ULong(const uint64_t min, const uint64_t max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

float_t Random::Float(const float_t min, const float_t max)
{
    std::uniform_real_distribution dist(min, max);
    return dist(engine);
}

double_t Random::Double(const double_t min, const double_t max)
{
    std::uniform_real_distribution dist(min, max);
    return dist(engine);
}

Color Random::Color(const Mountain::Color minValues, const Mountain::Color maxValues)
{
    return Mountain::Color(
        Float(minValues.r, maxValues.r),
        Float(minValues.g, maxValues.g),
        Float(minValues.b, maxValues.b),
        Float(minValues.a, maxValues.a)
    );
}

ColorHsva Random::ColorHsva(const Mountain::ColorHsva minValues, const Mountain::ColorHsva maxValues)
{
    return Mountain::ColorHsva(
        Float(minValues.h, maxValues.h),
        Float(minValues.s, maxValues.s),
        Float(minValues.v, maxValues.v),
        Float(minValues.a, maxValues.a)
    );
}

bool_t Random::Chance(const float_t probability)
{
    std::bernoulli_distribution dist(probability);
    return dist(engine);
}

Vector2 Random::PointInCircle(const Vector2 &center, const float_t radius)
{
    std::uniform_real_distribution<float_t> rdmAngle(0.f, static_cast<float_t>(std::numbers::pi) * 2.f);
    std::uniform_real_distribution<float_t> rdmRadius(0.f, radius);
    const float angle = rdmAngle(engine);
    return center + Vector2(std::cos(angle), std::sin(angle)) * rdmRadius(engine);
}

Vector2 Random::PointInRectangle(const Vector2 &position, const Vector2 &size)
{
    std::uniform_real_distribution x(position.x, position.x + size.x);
    std::uniform_real_distribution y(position.y, position.y + size.y);
    return Vector2(x(engine), y(engine));
}
