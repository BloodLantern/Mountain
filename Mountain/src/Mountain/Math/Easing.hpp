#pragma once

#include "Mountain/Core.hpp"

/// @file easing.hpp
/// @brief Defines the Easing namespace in which the common <a href="https://easings.net">easing functions</a> are defined.

/// @namespace Easing
/// @brief This namespace contains common <a href="https://easings.net">easing functions</a>.
namespace Easing
{
    /// @brief An Easer is a function that takes a value in the range [0, 1] and returns a new value in the same range.
    using Easer = f32(*)(f32);

    /// @brief Returns the given value unchanged.
    [[nodiscard]]
    MOUNTAIN_API constexpr f32 Linear(f32 t);

    /// @brief The <a href="https://easings.net/#easeInSine">SineIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 SineIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutSine">SineOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 SineOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutSine">SineInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 SineInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInQuad">QuadIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuadIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutQuad">QuadOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuadOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutQuad">QuadInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuadInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInCubic">CubicIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 CubicIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutCubic">CubicOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 CubicOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutCubic">CubicInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 CubicInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInQuart">QuartIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuartIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutQuart">QuartOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuartOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutQuart">QuartInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuartInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInQuint">QuintIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuintIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutQuint">QuintOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuintOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutQuint">QuintInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 QuintInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInExpo">ExpoIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 ExpoIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutExpo">ExpoOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 ExpoOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutExpo">ExpoInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 ExpoInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInCirc">CircIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 CircIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutCirc">CircOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 CircOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutCirc">CircInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 CircInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInBack">BackIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 BackIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutBack">BackOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 BackOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutBack">BackInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr f32 BackInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInElastic">ElasticIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 ElasticIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutElastic">ElasticOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 ElasticOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutElastic">ElasticInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 ElasticInOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInBounce">BounceIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 BounceIn(f32 t);

    /// @brief The <a href="https://easings.net/#easeOutBounce">BounceOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 BounceOut(f32 t);

    /// @brief The <a href="https://easings.net/#easeInOutBounce">BounceInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MOUNTAIN_API f32 BounceInOut(f32 t);
}

constexpr f32 Easing::Linear(const f32 t)
{
    return t;
}

constexpr f32 Easing::QuadIn(const f32 t)
{
    return t * t;
}

constexpr f32 Easing::QuadOut(const f32 t)
{
    return t * (2.f - t);
}

constexpr f32 Easing::QuadInOut(const f32 t)
{
    return t < 0.5f ? 2.f * t * t : t * (4.f - 2.f * t) - 1.f;
}

constexpr f32 Easing::CubicIn(const f32 t)
{
    return t * t * t;
}

constexpr f32 Easing::CubicOut(f32 t)
{
    t--;
    return 1.f + t * t * t;
}

constexpr f32 Easing::CubicInOut(const f32 t)
{
    if (t < 0.5f)
    {
        return 4.f * t * t * t;
    }

    const f32 t2 = t - 1.f;
    return 1.f + 4.f * t2 * t2 * t2;
}

constexpr f32 Easing::QuartIn(f32 t)
{
    t *= t;
    return t * t;
}

constexpr f32 Easing::QuartOut(const f32 t)
{
    f32 t2 = t - 1;
    t2 *= t2;
    return 1.f - t2 * t2;
}

constexpr f32 Easing::QuartInOut(f32 t)
{
    if (t < 0.5f)
    {
        t *= t;
        return 8.f * t * t;
    }
    else
    {
        t -= 1;
        t = t * t;
        return 1.f - 8.f * t * t;
    }
}

constexpr f32 Easing::QuintIn(const f32 t)
{
    const f32 t2 = t * t;
    return t * t2 * t2;
}

constexpr f32 Easing::QuintOut(f32 t)
{
    t -= 1;
    const f32 t2 = t * t;
    return 1.f + t * t2 * t2;
}

constexpr f32 Easing::QuintInOut(f32 t)
{
    f32 t2;
    if (t < 0.5f)
    {
        t2 = t * t;
        return 16.f * t * t2 * t2;
    }
    else
    {
        t -= 1;
        t2 = t * t;
        return 1.f + 16.f * t * t2 * t2;
    }
}

constexpr f32 Easing::BackIn(const f32 t)
{
    return t * t * (2.70158f * t - 1.70158f);
}

constexpr f32 Easing::BackOut(f32 t)
{
    t -= 1;
    return 1.f + t * t * (2.70158f * t + 1.70158f);
}

constexpr f32 Easing::BackInOut(f32 t)
{
    if (t < 0.5f)
    {
        return t * t * (7.f * t - 2.5f) * 2.f;
    }
    else
    {
        t -= 1;
        return 1.f + t * t * 2.f * (7.f * t + 2.5f);
    }
}
