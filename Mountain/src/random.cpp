#include "random.hpp"

#include <random>
#include <numbers>

std::random_device device;
std::mt19937 engine = std::mt19937(device());

short mountain::Random::NextShort(const short min, const short max)
{
    std::uniform_int_distribution<short> dist(min, max);
    return dist(engine);
}

unsigned short mountain::Random::NextUShort(const unsigned short min, const unsigned short max)
{
    std::uniform_int_distribution<unsigned short> dist(min, max);
    return dist(engine);
}

int mountain::Random::NextInt(const int min, const int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

unsigned int mountain::Random::NextUInt(const unsigned int min, const unsigned int max)
{
    std::uniform_int_distribution<unsigned int> dist(min, max);
    return dist(engine);
}

long mountain::Random::NextLong(const long min, const long max)
{
    std::uniform_int_distribution<long> dist(min, max);
    return dist(engine);
}

unsigned long mountain::Random::NextULong(const unsigned long min, const unsigned long max)
{
    std::uniform_int_distribution<unsigned long> dist(min, max);
    return dist(engine);
}

float mountain::Random::NextFloat(const float min, const float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine);
}

double mountain::Random::NextDouble(const double min, const double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(engine);
}

bool mountain::Random::Chance(const float probability)
{
    std::bernoulli_distribution dist(probability);
    return dist(engine);
}

Vector2 mountain::Random::PointInCircle(const Vector2 &center, const float radius)
{
    std::uniform_real_distribution<float> rdmAngle(0, (float) std::numbers::pi * 2);
    std::uniform_real_distribution<float> rdmRadius(0, radius);
    const float angle = rdmAngle(engine);
    return center + Vector2(std::cos(angle), std::sin(angle)) * rdmRadius(engine);
}

Vector2 mountain::Random::PointInRectangle(const Vector2 &position, const Vector2 &size)
{
    std::uniform_real_distribution<float> x(position.x, position.x + size.x);
    std::uniform_real_distribution<float> y(position.y, position.y + size.y);
    return Vector2(x(engine), y(engine));
}
