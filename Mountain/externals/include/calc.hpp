#pragma once

#include <cmath>
#include <algorithm>

namespace calc
{
    /// @brief The Earth gravitational constant
    constexpr float Gravity = 9.80665f;

    [[nodiscard]] constexpr char Sign(const float value)
    {
        // std::signbit returns whether the value is negative
        return std::signbit(value) ? -1 : 1;
    }

    static void Approach(float& value, const float target, const float step)
    {
        const float difference = target - value;

        // If the target value hasn't been reached yet
        if (std::abs(difference) > 0)
        {
            value += std::min(step, std::abs(difference)) * Sign(difference);
        }
    }
}
