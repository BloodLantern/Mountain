#pragma once

#include "Mountain/core.hpp"

#include <limits>

#include <Maths/vector2.hpp>

#include "Mountain/utils/color.hpp"

BEGIN_MOUNTAIN

class Random
{
    STATIC_CLASS(Random)
    
public:
    static int8_t SByte(int8_t min = std::numeric_limits<int8_t>::min(), int8_t max = std::numeric_limits<int8_t>::max());
    static uint8_t Byte(uint8_t min = std::numeric_limits<uint8_t>::min(), uint8_t max = std::numeric_limits<uint8_t>::max());
    static int16_t Short(int16_t min = std::numeric_limits<int16_t>::min(), int16_t max = std::numeric_limits<int16_t>::max());
    static uint16_t UShort(uint16_t min = std::numeric_limits<uint16_t>::min(), uint16_t max = std::numeric_limits<uint16_t>::max());
    static int32_t Int(int32_t min = std::numeric_limits<int32_t>::min(), int32_t max = std::numeric_limits<int32_t>::max());
    static uint32_t UInt(uint32_t min = std::numeric_limits<uint32_t>::min(), uint32_t max = std::numeric_limits<uint32_t>::max());
    static int64_t Long(int64_t min = std::numeric_limits<int64_t>::min(), int64_t max = std::numeric_limits<int64_t>::max());
    static uint64_t ULong(uint64_t min = std::numeric_limits<uint64_t>::min(), uint64_t max = std::numeric_limits<uint64_t>::max());
    static float_t Float(float_t min = std::numeric_limits<float_t>::min(), float_t max = std::numeric_limits<float_t>::max());
    static double_t Double(double_t min = std::numeric_limits<double_t>::min(), double_t max = std::numeric_limits<double_t>::max());

    static Color Color(Color minValues = Color::Black(), Color maxValues = Color::White());
    static ColorHsva ColorHsva(ColorHsva minValues, ColorHsva maxValues);

    /// @brief Returns true if the given probability have been met.
    /// @param probability The probability to check in the range [0, 1].
    /// @return True if the given probability have been met, false otherwise.
    static bool_t Chance(float_t probability = 0.5f);

    static Vector2 PointInCircle(const Vector2& center = Vector2::Zero(), float_t radius = 1);
    static Vector2 PointInRectangle(const Vector2& position = Vector2::Zero(), const Vector2& size = Vector2::One());
};

END_MOUNTAIN
