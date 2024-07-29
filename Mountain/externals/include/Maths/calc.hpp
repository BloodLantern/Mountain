#pragma once

#include <algorithm>
#include <numbers>

#include "definitions.hpp"

/// @file calc.hpp
/// @brief A collection of general-use constants and useful functions.

#ifndef ZERO
/// @brief The value to set @ref Calc::Zero to.
///
/// Can be overridden by defining it with a different value before including this file.
///
///	This macro is undefined at the end of this file. To access this value,
///	the @ref Calc::Zero constant should be used instead.
#define ZERO 1e-6f
#endif

/// @namespace Calc
/// @brief This namespace contains mathematical constants and useful functions/macros.
namespace Calc
{
	/// @brief The value under which a number is considered to be zero.
	constexpr float_t Zero = ZERO;
	
	/// @brief Shorthand for writing <c>std::numbers::pi_v<float_t></c>.
	constexpr float_t Pi = std::numbers::pi_v<float_t>;
	
	/// @brief Shorthand for writing <c>Calc::Pi * 2.f</c>.
	constexpr float_t TwoPi = Pi * 2.f;
	
	/// @brief Shorthand for writing <c>Calc::Pi / 2.f</c>.
	constexpr float_t PiOver2 = Pi / 2.f;
	
	/// @brief Shorthand for writing <c>Calc::Pi / 2.f</c>.
	constexpr float_t PiOver4 = Pi / 4.f;
	
	/// @brief Value used to convert from degrees to radians.
	constexpr float_t Deg2Rad = Pi / 180.f;
	
	/// @brief Value used to convert from radians to degrees.
	constexpr float_t Rad2Deg = 1.f / Deg2Rad;

    /// @brief Returns -1 if x is less than 0, 1 if x is greater than 0 and 0 if x is equal to 0.
    /// 
    /// @param number The number to get the sign of.
    /// @returns -1 if the value is negative, 1 if it is positive. 0 Otherwise.
    [[nodiscard]]
	MATH_TOOLBOX constexpr float_t Sign(float_t number) noexcept;

    /// @brief	A constexpr version of the <c>std::abs</c> function.
    /// 
    /// @param number The number to get the absolute value of.
    /// @returns The absolute value of @p number.
    [[nodiscard]]
    MATH_TOOLBOX constexpr float_t Abs(float_t number) noexcept;

    /// @brief	A constexpr version of the <c>std::round</c> function.
    /// 
    /// @param number The number to round to the nearest integer value.
    /// @returns The rounded value of @p number.
    [[nodiscard]]
    MATH_TOOLBOX constexpr float_t Round(float_t number) noexcept;

    /// @brief	A constexpr version of the <c>std::floor</c> function.
    /// 
    /// @param number The number to floor.
    /// @returns The floor value of @p number.
    [[nodiscard]]
    MATH_TOOLBOX constexpr float_t Floor(float_t number) noexcept;

    /// @brief	A constexpr version of the <c>std::ceil</c> function.
    /// 
    /// @param number The number to ceil.
    /// @returns The ceil value of @p number.
    [[nodiscard]]
    MATH_TOOLBOX constexpr float_t Ceil(float_t number) noexcept;

	/// @brief	A constexpr version of the <c>std::fmodf</c> function.
	/// 
	/// @param a The left-hand side of the modulo.
	/// @param b The right-hand side of the modulo.
	/// @returns The modulo of @p a by @p b.
	[[nodiscard]]
	MATH_TOOLBOX constexpr float_t Modulo(float_t a, float_t b) noexcept;

	/// @brief Approaches the target value by the given step size without ever exceeding it.
	/// 
	/// @param value The value to change.
	/// @param target The target value.
	/// @param step The step size.
	MATH_TOOLBOX constexpr void Approach(float_t& value, float_t target, float_t step) noexcept;

	/// @brief Given a value between 0 and 1, returns a value going from 0 to 1 and to 0 again.
	/// 
	/// @param value The YoYo value.
	/// @returns A value between 0 and 1, closer to 1 if the input value is close to 0.5.
	[[nodiscard]]
	MATH_TOOLBOX constexpr float_t YoYo(float_t value) noexcept;

	/// @brief Returns true on an interval.
	/// 
	/// @param value The current time value.
	/// @param lastValue The last time value. (last call)
	/// @param interval The interval.
	[[nodiscard]]
	MATH_TOOLBOX constexpr bool_t OnInterval(float_t value, float_t lastValue, float_t interval);

    /// @brief Checks if a value is less than what is considered to be zero, e.g. if its absolute value is smaller than <see cref="Calc::Zero"/>.
    /// 
    /// @param value The value to check.
    /// @returns Whether the value is considered to be zero.
    [[nodiscard]]
    MATH_TOOLBOX constexpr bool_t IsZero(float_t value) noexcept;

    /// @brief Checks if a value is less than what is considered to be zero, e.g. if its absolute value is smaller than <paramref name="zero"/>.
    /// 
    /// @param value The value to check.
    /// @param zero The value under which a number is considered to be zero.
    /// @returns Whether the value is considered to be zero.
    [[nodiscard]]
    MATH_TOOLBOX constexpr bool_t IsZero(float_t value, float_t zero) noexcept;

    /// @brief If a value is considered zero using IsZero(float_t), returns 0. Otherwise, returns the given value.
    /// 
    /// @param value The value to check.
    /// @returns Whether the value is considered to be zero.
    [[nodiscard]]
    MATH_TOOLBOX constexpr float_t MakeZero(float_t value) noexcept;

    /// @brief If a value is considered zero using IsZero(float_t, float_t), returns 0. Otherwise, returns the given value.
    /// 
    /// @param value The value to check.
    /// @param zero The value under which a number is considered to be zero.
    /// @returns Whether the value is considered to be zero.
    [[nodiscard]]
    MATH_TOOLBOX constexpr float_t MakeZero(float_t value, float_t zero) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX constexpr bool_t Equals(float_t a, float_t b) noexcept;
}

constexpr float_t Calc::Sign(const float_t number) noexcept { return number < 0.f ? -1.f : 1.f; }

constexpr float_t Calc::Abs(const float_t number) noexcept { return number < 0.f ? -number : number; }

constexpr float_t Calc::Round(const float_t number) noexcept
{
    const int32_t lower = static_cast<int32_t>(number);
    const int32_t upper = static_cast<int32_t>(number + 0.5f);

    return static_cast<float_t>(lower < upper ? upper : lower);
}

constexpr float_t Calc::Floor(const float_t number) noexcept { return Round(number - 0.5f); }

constexpr float_t Calc::Ceil(const float_t number) noexcept { return Round(number + 0.5f); }

constexpr float_t Calc::Modulo(const float_t a, const float_t b) noexcept { return a - static_cast<float_t>(static_cast<int64_t>(a / b)) * b; }

// Undef windows macro to be able to use std::min without conflicts
#undef min

constexpr void Calc::Approach(float_t &value, const float_t target, const float_t step) noexcept
{
	// If the target value hasn't been reached yet
	if (!Equals(value, target))
	{
		const float_t difference = target - value;
		value += std::min(step, Abs(difference)) * Sign(difference);
	}
}

constexpr float_t Calc::YoYo(const float_t value) noexcept { return value <= 0.5f ? value * 2.f : 1.f - (value - 0.5f) * 2.f; }

constexpr bool_t Calc::OnInterval(float_t value, float_t lastValue, float_t interval) { return Calc::IsZero(interval) || (int) (lastValue / interval) != (int) (value / interval); }

constexpr bool_t Calc::IsZero(const float_t value) noexcept { return IsZero(value, Zero); }

constexpr bool_t Calc::IsZero(const float_t value, const float_t zero) noexcept { return Abs(value) <= zero; }

constexpr float_t Calc::MakeZero(const float_t value) noexcept { return MakeZero(value, Zero); }

constexpr float_t Calc::MakeZero(const float_t value, const float_t zero) noexcept { return IsZero(value, zero) ? 0.f : value; }

constexpr bool_t Calc::Equals(const float_t a, const float_t b) noexcept { return IsZero(a - b); }

#undef ZERO
