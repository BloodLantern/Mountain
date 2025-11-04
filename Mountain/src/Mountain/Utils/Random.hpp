#pragma once

#include "Mountain/Core.hpp"

#include <limits>
#include <random>

#include <Math/vector2.hpp>

#include "Mountain/Utils/Color.hpp"

namespace Mountain
{
    class Random
    {
    public:
        MOUNTAIN_API static Random& Instance();

        MOUNTAIN_API Random();
        MOUNTAIN_API explicit Random(std::default_random_engine::result_type seed);

        MOUNTAIN_API int8_t SByte(int8_t minInclusive = std::numeric_limits<int8_t>::min(), int8_t maxExclusive = std::numeric_limits<int8_t>::max());
        MOUNTAIN_API uint8_t Byte(uint8_t minInclusive = std::numeric_limits<uint8_t>::min(), uint8_t maxExclusive = std::numeric_limits<uint8_t>::max());
        MOUNTAIN_API int16_t Short(int16_t minInclusive = std::numeric_limits<int16_t>::min(), int16_t maxExclusive = std::numeric_limits<int16_t>::max());
        MOUNTAIN_API uint16_t UShort(uint16_t minInclusive = std::numeric_limits<uint16_t>::min(), uint16_t maxExclusive = std::numeric_limits<uint16_t>::max());
        MOUNTAIN_API int32_t Int(int32_t minInclusive = std::numeric_limits<int32_t>::min(), int32_t maxExclusive = std::numeric_limits<int32_t>::max());
        MOUNTAIN_API uint32_t UInt(uint32_t minInclusive = std::numeric_limits<uint32_t>::min(), uint32_t maxExclusive = std::numeric_limits<uint32_t>::max());
        MOUNTAIN_API int64_t Long(int64_t minInclusive = std::numeric_limits<int64_t>::min(), int64_t maxExclusive = std::numeric_limits<int64_t>::max());
        MOUNTAIN_API uint64_t ULong(uint64_t minInclusive = std::numeric_limits<uint64_t>::min(), uint64_t maxExclusive = std::numeric_limits<uint64_t>::max());
        MOUNTAIN_API float_t Float(float_t minInclusive = std::numeric_limits<float_t>::min(), float_t maxExclusive = std::numeric_limits<float_t>::max());
        MOUNTAIN_API double_t Double(double_t minInclusive = std::numeric_limits<double_t>::min(), double_t maxExclusive = std::numeric_limits<double_t>::max());

        MOUNTAIN_API Color Color(Color minValuesInclusive = Color::Black(), Color maxValuesInclusive = Color::White());
        MOUNTAIN_API ColorHsva ColorHsva(ColorHsva minValuesInclusive = { 0.f, 0.f, 0.f, 0.f }, ColorHsva maxValuesInclusive = { 1.f, 1.f, 1.f, 1.f });

        /// @brief Returns true if the given probability has been met.
        /// @param probability The probability to check in the range [0, 1].
        MOUNTAIN_API bool_t Chance(float_t probability = 0.5f);

        MOUNTAIN_API Vector2 PointInCircle(const Vector2& center = Vector2::Zero(), float_t radius = 1);
        MOUNTAIN_API Vector2 PointInRectangle(const Vector2& position = Vector2::Zero(), const Vector2& size = Vector2::One());

        MOUNTAIN_API Vector2 Direction();

    private:
        static inline std::random_device device;
        static Random instance;

        std::default_random_engine m_Engine;
    };
};
