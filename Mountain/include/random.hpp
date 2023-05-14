#pragma once

#include <vector2.hpp>

#include <limits>

namespace mountain
{
    class Random
    {
    public:
        Random() = delete;

        static short NextShort(const short min = std::numeric_limits<short>::min(), const short max = std::numeric_limits<short>::max());
        static unsigned short NextUShort(const unsigned short min = 0, const unsigned short max = std::numeric_limits<unsigned short>::max());
        static int NextInt(const int min = std::numeric_limits<int>::min(), const int max = std::numeric_limits<int>::max());
        static unsigned int NextUInt(const unsigned int min = 0, const unsigned int max = std::numeric_limits<unsigned int>::max());
        static long NextLong(const long min = std::numeric_limits<long>::min(), const long max = std::numeric_limits<long>::max());
        static unsigned long NextULong(const unsigned long min = 0, const unsigned long max = std::numeric_limits<unsigned long>::max());
        static float NextFloat(const float min = std::numeric_limits<float>::min(), const float max = std::numeric_limits<float>::max());
        static double NextDouble(const double min = std::numeric_limits<double>::min(), const double max = std::numeric_limits<double>::max());

        /// @brief Returns true if the given probability have been met.
        /// @param probability The probability to check in the range [0, 1].
        /// @return True if the given probability have been met, false otherwise.
        static bool Chance(const float probability = 0.5f);

        static Vector2 PointInCircle(const Vector2& center = 0, const float radius = 1);
        static Vector2 PointInRectangle(const Vector2& position = 0, const Vector2& size = 1);
    };
}
