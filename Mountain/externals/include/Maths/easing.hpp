#pragma once

#include "calc.hpp"

/// @file easing.hpp
/// @brief Defines the Easing namespace in which the common <a href="https://easings.net">easing functions</a> are defined.

/// @namespace Easing
/// @brief This namespace contains common <a href="https://easings.net">easing functions</a>.
namespace Easing
{
    /// @brief The <a href="https://easings.net/#easeInSine">SineIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float SineIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutSine">SineOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float SineOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutSine">SineInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float SineInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInQuad">QuadIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuadIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutQuad">QuadOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuadOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutQuad">QuadInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuadInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInCubic">CubicIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float CubicIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutCubic">CubicOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float CubicOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutCubic">CubicInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float CubicInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInQuart">QuartIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuartIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutQuart">QuartOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuartOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutQuart">QuartInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuartInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInQuint">QuintIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuintIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutQuint">QuintOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuintOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutQuint">QuintInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float QuintInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInExpo">ExpoIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float ExpoIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutExpo">ExpoOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float ExpoOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutExpo">ExpoInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float ExpoInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInCirc">CircIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float CircIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutCirc">CircOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float CircOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutCirc">CircInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float CircInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInBack">BackIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float BackIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutBack">BackOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float BackOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutBack">BackInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    constexpr float BackInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInElastic">ElasticIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float ElasticIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutElastic">ElasticOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float ElasticOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutElastic">ElasticInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float ElasticInOut(float t);

    /// @brief The <a href="https://easings.net/#easeInBounce">BounceIn</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float BounceIn(float t);

    /// @brief The <a href="https://easings.net/#easeOutBounce">BounceOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float BounceOut(float t);

    /// @brief The <a href="https://easings.net/#easeInOutBounce">BounceInOut</a> easing function.
    ///
    /// @param t The current time. Must be between 0 and 1 inclusive.
    /// @return The transformed time.
    [[nodiscard]]
    MATH_TOOLBOX float BounceInOut(float t);
}

constexpr float Easing::QuadIn(const float t)
{
    return t * t;
}

constexpr float Easing::QuadOut(const float t)
{
    return t * (2.f - t);
}

constexpr float Easing::QuadInOut(const float t)
{
    return t < 0.5f ? 2.f * t * t : t * (4.f - 2.f * t) - 1.f;
}

constexpr float Easing::CubicIn(const float t)
{
    return t * t * t;
}

constexpr float Easing::CubicOut(float t)
{
    t--;
    return 1.f + t * t * t;
}

constexpr float Easing::CubicInOut(const float t)
{
    float t2 = t - 1;
    float t3 = t2 - 1;
    return t < 0.5f ? 4.f * t * t * t : 1.f + t2 * (2.f * t3) * (2.f * t3);
}

constexpr float Easing::QuartIn(float t)
{
    t *= t;
    return t * t;
}

constexpr float Easing::QuartOut(const float t)
{
    float t2 = t - 1;
    t2 *= t2;
    return 1.f - t2 * t2;
}

constexpr float Easing::QuartInOut(float t)
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

constexpr float Easing::QuintIn(const float t)
{
    float t2 = t * t;
    return t * t2 * t2;
}

constexpr float Easing::QuintOut(float t)
{
    t -= 1;
    float t2 = t * t;
    return 1.f + t * t2 * t2;
}

constexpr float Easing::QuintInOut(float t)
{
    float t2;
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

constexpr float Easing::BackIn(const float t)
{
    return t * t * (2.70158f * t - 1.70158f);
}

constexpr float Easing::BackOut(float t)
{
    t -= 1;
    return 1.f + t * t * (2.70158f * t + 1.70158f);
}

constexpr float Easing::BackInOut(float t)
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
