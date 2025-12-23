#pragma once

#include <limits>
#include <random>

#include "Mountain/Core.hpp"
#include "Mountain/Math/Vector2.hpp"
#include "Mountain/Utils/Color.hpp"

namespace Mountain
{
    class Random
    {
    public:
        MOUNTAIN_API static Random& Instance();

        MOUNTAIN_API Random();
        MOUNTAIN_API explicit Random(std::default_random_engine::result_type seed);

        MOUNTAIN_API s8 SByte(s8 minInclusive = std::numeric_limits<s8>::min(), s8 maxExclusive = std::numeric_limits<s8>::max());
        MOUNTAIN_API u8 Byte(u8 minInclusive = std::numeric_limits<u8>::min(), u8 maxExclusive = std::numeric_limits<u8>::max());
        MOUNTAIN_API s16 Short(s16 minInclusive = std::numeric_limits<s16>::min(), s16 maxExclusive = std::numeric_limits<s16>::max());
        MOUNTAIN_API u16 UShort(u16 minInclusive = std::numeric_limits<u16>::min(), u16 maxExclusive = std::numeric_limits<u16>::max());
        MOUNTAIN_API s32 Int(s32 minInclusive = std::numeric_limits<s32>::min(), s32 maxExclusive = std::numeric_limits<s32>::max());
        MOUNTAIN_API u32 UInt(u32 minInclusive = std::numeric_limits<u32>::min(), u32 maxExclusive = std::numeric_limits<u32>::max());
        MOUNTAIN_API s64 Long(s64 minInclusive = std::numeric_limits<s64>::min(), s64 maxExclusive = std::numeric_limits<s64>::max());
        MOUNTAIN_API u64 ULong(u64 minInclusive = std::numeric_limits<u64>::min(), u64 maxExclusive = std::numeric_limits<u64>::max());
        MOUNTAIN_API f32 Float(f32 minInclusive = std::numeric_limits<f32>::min(), f32 maxExclusive = std::numeric_limits<f32>::max());
        MOUNTAIN_API f64 Double(f64 minInclusive = std::numeric_limits<f64>::min(), f64 maxExclusive = std::numeric_limits<f64>::max());

        MOUNTAIN_API Color Color(Color minValuesInclusive = Color::Black(), Color maxValuesInclusive = Color::White());
        MOUNTAIN_API ColorHsva ColorHsva(ColorHsva minValuesInclusive = { 0.f, 0.f, 0.f, 0.f }, ColorHsva maxValuesInclusive = { 1.f, 1.f, 1.f, 1.f });

        /// @brief Returns true if the given probability has been met.
        /// @param probability The probability to check in the range [0, 1].
        MOUNTAIN_API bool Chance(f32 probability = 0.5f);

        MOUNTAIN_API Vector2 PointInCircle(const Vector2& center = Vector2::Zero(), f32 radius = 1);
        MOUNTAIN_API Vector2 PointInRectangle(const Vector2& position = Vector2::Zero(), const Vector2& size = Vector2::One());

        MOUNTAIN_API Vector2 Direction();

    private:
        static inline std::random_device device;
        static Random instance;

        std::default_random_engine m_Engine;
    };
};
