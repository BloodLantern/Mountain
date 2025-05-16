#pragma once

#include "Maths/core.hpp"

/// @file easing.hpp
/// @brief Defines the Easing namespace in which the common <a href="https://easings.net">easing functions</a> are defined.

/// @namespace Easing
/// @brief This namespace contains common <a href="https://easings.net">easing functions</a>.
namespace Easing
{
    /// @brief An Easer is a function that takes a value in the range [0, 1] and returns a new value in the same range.
    using Easer = float_t(*)(float_t);
    
    /// @brief The <a href="https://easings.net/#easeInSine">SineIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t SineIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutSine">SineOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t SineOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutSine">SineInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t SineInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInQuad">QuadIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuadIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutQuad">QuadOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuadOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutQuad">QuadInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuadInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInCubic">CubicIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t CubicIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutCubic">CubicOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t CubicOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutCubic">CubicInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t CubicInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInQuart">QuartIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuartIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutQuart">QuartOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuartOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutQuart">QuartInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuartInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInQuint">QuintIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuintIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutQuint">QuintOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuintOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutQuint">QuintInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t QuintInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInExpo">ExpoIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t ExpoIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutExpo">ExpoOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t ExpoOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutExpo">ExpoInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t ExpoInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInCirc">CircIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t CircIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutCirc">CircOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t CircOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutCirc">CircInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t CircInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInBack">BackIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t BackIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutBack">BackOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t BackOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutBack">BackInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float_t BackInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInElastic">ElasticIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t ElasticIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutElastic">ElasticOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t ElasticOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutElastic">ElasticInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t ElasticInOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInBounce">BounceIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t BounceIn(float_t t);

    /// @brief The <a href="https://easings.net/#easeOutBounce">BounceOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t BounceOut(float_t t);

    /// @brief The <a href="https://easings.net/#easeInOutBounce">BounceInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float_t BounceInOut(float_t t);
}

constexpr float_t Easing::QuadIn(const float_t t)
{
    return t * t;
}

constexpr float_t Easing::QuadOut(const float_t t)
{
    return t * (2.f - t);
}

constexpr float_t Easing::QuadInOut(const float_t t)
{
    return t < 0.5f ? 2.f * t * t : t * (4.f - 2.f * t) - 1.f;
}

constexpr float_t Easing::CubicIn(const float_t t)
{
    return t * t * t;
}

constexpr float_t Easing::CubicOut(float_t t)
{
    t--;
    return 1.f + t * t * t;
}

constexpr float_t Easing::CubicInOut(const float_t t)
{
    const float_t t2 = t - 1;
    const float_t t3 = t2 - 1;
    return t < 0.5f ? 4.f * t * t * t : 1.f + t2 * (2.f * t3) * (2.f * t3);
}

constexpr float_t Easing::QuartIn(float_t t)
{
    t *= t;
    return t * t;
}

constexpr float_t Easing::QuartOut(const float_t t)
{
    float_t t2 = t - 1;
    t2 *= t2;
    return 1.f - t2 * t2;
}

constexpr float_t Easing::QuartInOut(float_t t)
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

constexpr float_t Easing::QuintIn(const float_t t)
{
    const float_t t2 = t * t;
    return t * t2 * t2;
}

constexpr float_t Easing::QuintOut(float_t t)
{
    t -= 1;
    const float_t t2 = t * t;
    return 1.f + t * t2 * t2;
}

constexpr float_t Easing::QuintInOut(float_t t)
{
    float_t t2;
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

constexpr float_t Easing::BackIn(const float_t t)
{
    return t * t * (2.70158f * t - 1.70158f);
}

constexpr float_t Easing::BackOut(float_t t)
{
    t -= 1;
    return 1.f + t * t * (2.70158f * t + 1.70158f);
}

constexpr float_t Easing::BackInOut(float_t t)
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
