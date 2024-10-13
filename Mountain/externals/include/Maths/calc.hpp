#pragma once

#include <algorithm>
#include <numbers>

#include "Maths/core.hpp"
#include "Maths/easing.hpp"
#include "Maths/vector2.hpp"
#include "Maths/vector3.hpp"
#include "Maths/vector4.hpp"

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

class Matrix2;
class Matrix3;
class Matrix;
class Quaternion;
class Vector2;
class Vector3;
class Vector4;

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
	
	/// @brief Shorthand for writing <c>Calc::Pi / 4.f</c>.
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

	/// @brief	A constexpr version of the <c>std::abs</c> function for Vector2.
	/// 
	/// @param vector The vector to get the absolute value of.
	/// @returns A Vector2 whose components are the absolute values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector2 Abs(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the <c>std::abs</c> function for Vector3.
	/// 
	/// @param vector The vector to get the absolute value of.
	/// @returns A Vector3 whose components are the absolute values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector3 Abs(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the <c>std::abs</c> function for Vector4.
	/// 
	/// @param vector The vector to get the absolute value of.
	/// @returns A Vector4 whose components are the absolute values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector4 Abs(const Vector4& vector) noexcept;

	/// @brief	A constexpr version of the <c>std::round</c> function.
	/// 
	/// @param number The number to round to the nearest integer value.
	/// @returns The rounded value of @p number.
	[[nodiscard]]
	MATH_TOOLBOX constexpr float_t Round(float_t number) noexcept;

	/// @brief	A constexpr version of the <c>std::round</c> function for Vector2.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector2 whose components are the rounded values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector2 Round(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the <c>std::round</c> function for Vector3.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector3 whose components are the rounded values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector3 Round(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the <c>std::round</c> function for Vector4.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector4 whose components are the rounded values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector4 Round(const Vector4& vector) noexcept;

    /// @brief	A constexpr version of the <c>std::floor</c> function.
    /// 
    /// @param number The number to floor.
    /// @returns The floor value of @p number.
    [[nodiscard]]
	MATH_TOOLBOX constexpr float_t Floor(float_t number) noexcept;

	/// @brief	A constexpr version of the <c>std::floor</c> function for Vector2.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector2 whose components are the floored values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector2 Floor(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the <c>std::floor</c> function for Vector3.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector3 whose components are the floored values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector3 Floor(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the <c>std::floor</c> function for Vector4.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector4 whose components are the floored values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector4 Floor(const Vector4& vector) noexcept;

    /// @brief	A constexpr version of the <c>std::ceil</c> function.
    /// 
    /// @param number The number to ceil.
    /// @returns The ceil value of @p number.
    [[nodiscard]]
	MATH_TOOLBOX constexpr float_t Ceil(float_t number) noexcept;

	/// @brief	A constexpr version of the <c>std::ceil</c> function for Vector2.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector2 whose components are the ceiled values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector2 Ceil(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the <c>std::ceil</c> function for Vector3.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector3 whose components are the ceiled values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector3 Ceil(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the <c>std::ceil</c> function for Vector4.
	/// 
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector4 whose components are the ceiled values of @p vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector4 Ceil(const Vector4& vector) noexcept;

	/// @brief	A constexpr version of the <c>std::clamp</c> function.
	/// 
	/// @param number The number to clamp between two values.
	/// @param min The minimum value.
	/// @param max The maximum value.
	/// @returns The clamped number.
	[[nodiscard]]
	MATH_TOOLBOX constexpr float_t Clamp(float_t number, float_t min, float_t max) noexcept;

	/// @brief	A constexpr version of the <c>std::clamp</c> function for Vector2.
	/// 
	/// @param vector The vector to clamp between two positions.
	/// @param min The minimum position.
	/// @param max The maximum position.
	/// @returns The clamped vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector2 Clamp(Vector2 vector, Vector2 min, Vector2 max) noexcept;

	/// @brief	A constexpr version of the <c>std::clamp</c> function for Vector3.
	/// 
	/// @param vector The vector to clamp between two positions.
	/// @param min The minimum position.
	/// @param max The maximum position.
	/// @returns The clamped vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector3 Clamp(const Vector3& vector, const Vector3& min, const Vector3& max) noexcept;

	/// @brief	A constexpr version of the <c>std::clamp</c> function for Vector4.
	/// 
	/// @param vector The vector to clamp between two positions.
	/// @param min The minimum position.
	/// @param max The maximum position.
	/// @returns The clamped vector.
	[[nodiscard]]
	MATH_TOOLBOX constexpr Vector4 Clamp(const Vector4& vector, const Vector4& min, const Vector4& max) noexcept;

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

	/// @brief Clamps the given @p value between @p min and @p max and remaps the result between @p newMin and @p newMax
	[[nodiscard]]
	MATH_TOOLBOX constexpr float_t ClampedMap(
		float_t value,
		float_t min,
		float_t max,
		float_t newMin = 0.f,
		float_t newMax = 1.f
	);

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

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX constexpr bool_t Equals(Vector2 a, Vector2 b) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX constexpr bool_t Equals(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX constexpr bool_t Equals(const Vector4& a, const Vector4& b) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX bool_t Equals(const Matrix2& a, const Matrix2& b) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX bool_t Equals(const Matrix3& a, const Matrix3& b) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX bool_t Equals(const Matrix& a, const Matrix& b) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(float_t).
	/// 
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	[[nodiscard]]
	MATH_TOOLBOX bool_t Equals(const Quaternion& a, const Quaternion& b) noexcept;
	
	[[nodiscard]]
	constexpr float_t Lerp(float_t value, float_t target, float_t time);
	
	[[nodiscard]]
	constexpr float_t Lerp(float_t value, float_t target, float_t time, Easing::Easer easer);
	
	[[nodiscard]]
	constexpr Vector2 Lerp(Vector2 value, Vector2 target, float_t time);
	
	[[nodiscard]]
	constexpr Vector2 Lerp(Vector2 value, Vector2 target, float_t time, Easing::Easer easer);
	
	[[nodiscard]]
	constexpr Vector3 Lerp(const Vector3& value, const Vector3& target, float_t time);
	
	[[nodiscard]]
	constexpr Vector3 Lerp(const Vector3& value, const Vector3& target, float_t time, Easing::Easer easer);
	
	[[nodiscard]]
	constexpr Vector4 Lerp(const Vector4& value, const Vector4& target, float_t time);
	
	[[nodiscard]]
	constexpr Vector4 Lerp(const Vector4& value, const Vector4& target, float_t time, Easing::Easer easer);
}

constexpr float_t Calc::Sign(const float_t number) noexcept { return number < 0.f ? -1.f : 1.f; }

constexpr float_t Calc::Abs(const float_t number) noexcept { return number < 0.f ? -number : number; }

constexpr Vector2 Calc::Abs(const Vector2 vector) noexcept { return { Abs(vector.x), Abs(vector.y) }; }

constexpr Vector3 Calc::Abs(const Vector3& vector) noexcept { return { Abs(vector.x), Abs(vector.y), Abs(vector.z) }; }

constexpr Vector4 Calc::Abs(const Vector4& vector) noexcept { return { Abs(vector.x), Abs(vector.y), Abs(vector.z), Abs(vector.w) }; }

constexpr float_t Calc::Round(const float_t number) noexcept
{
    const int32_t lower = static_cast<int32_t>(number);
    const int32_t upper = static_cast<int32_t>(number + 0.5f);  // NOLINT(bugprone-incorrect-roundings)

    return static_cast<float_t>(lower < upper ? upper : lower);
}

constexpr Vector2 Calc::Round(const Vector2 vector) noexcept { return { Round(vector.x), Round(vector.y) }; }

constexpr Vector3 Calc::Round(const Vector3& vector) noexcept { return { Round(vector.x), Round(vector.y), Round(vector.z) }; }

constexpr Vector4 Calc::Round(const Vector4& vector) noexcept { return { Round(vector.x), Round(vector.y), Round(vector.z), Round(vector.w) }; }

constexpr float_t Calc::Floor(const float_t number) noexcept { return Round(number - 0.5f); }

constexpr Vector2 Calc::Floor(const Vector2 vector) noexcept { return { Floor(vector.x), Floor(vector.y) }; }

constexpr Vector3 Calc::Floor(const Vector3& vector) noexcept { return { Floor(vector.x), Floor(vector.y), Floor(vector.z) }; }

constexpr Vector4 Calc::Floor(const Vector4& vector) noexcept { return { Floor(vector.x), Floor(vector.y), Floor(vector.z), Floor(vector.w) }; }

constexpr float_t Calc::Ceil(const float_t number) noexcept { return Round(number + 0.5f); }

constexpr Vector2 Calc::Ceil(const Vector2 vector) noexcept { return { Ceil(vector.x), Ceil(vector.y) }; }

constexpr Vector3 Calc::Ceil(const Vector3& vector) noexcept { return { Ceil(vector.x), Ceil(vector.y), Ceil(vector.z) }; }

constexpr Vector4 Calc::Ceil(const Vector4& vector) noexcept { return { Ceil(vector.x), Ceil(vector.y), Ceil(vector.z), Ceil(vector.w) }; }

constexpr float_t Calc::Clamp(const float_t number, const float_t min, const float_t max) noexcept
{
	if (number < min)
		return min;
	if (number > max)
		return max;
	return number;
}

constexpr Vector2 Calc::Clamp(const Vector2 vector, const Vector2 min, const Vector2 max) noexcept
{
	return { Clamp(vector.x, min.x, max.x), Clamp(vector.y, min.y, max.y) };
}

constexpr Vector3 Calc::Clamp(const Vector3& vector, const Vector3& min, const Vector3& max) noexcept
{
	return { Clamp(vector.x, min.x, max.x), Clamp(vector.y, min.y, max.y), Clamp(vector.z, min.z, max.z) };
}

constexpr Vector4 Calc::Clamp(const Vector4& vector, const Vector4& min, const Vector4& max) noexcept
{
	return { Clamp(vector.x, min.x, max.x), Clamp(vector.y, min.y, max.y), Clamp(vector.z, min.z, max.z), Clamp(vector.w, min.w, max.w) };
}

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

constexpr bool_t Calc::OnInterval(const float_t value, const float_t lastValue, const float_t interval)
{
	return IsZero(interval) || static_cast<int32_t>(lastValue / interval) != static_cast<int32_t>(value / interval);
}

constexpr float_t Calc::ClampedMap(const float_t value, const float_t min, const float_t max, const float_t newMin, const float_t newMax)
{
	return Clamp((value - min) / (max - min), 0.f, 1.f) * (newMax - newMin) + newMin;
}

constexpr bool_t Calc::IsZero(const float_t value) noexcept { return IsZero(value, Zero); }

constexpr bool_t Calc::IsZero(const float_t value, const float_t zero) noexcept { return Abs(value) <= zero; }

constexpr float_t Calc::MakeZero(const float_t value) noexcept { return MakeZero(value, Zero); }

constexpr float_t Calc::MakeZero(const float_t value, const float_t zero) noexcept { return IsZero(value, zero) ? 0.f : value; }

constexpr bool_t Calc::Equals(const float_t a, const float_t b) noexcept { return IsZero(a - b); }

constexpr bool_t Calc::Equals(const Vector2 a, const Vector2 b) noexcept { return Equals(a.x, b.x) && Equals(a.y, b.y); }

constexpr bool_t Calc::Equals(const Vector3& a, const Vector3& b) noexcept { return Equals(a.x, b.x) && Equals(a.y, b.y) && Equals(a.z, b.z); }

constexpr bool_t Calc::Equals(const Vector4& a, const Vector4& b) noexcept { return Equals(a.x, b.x) && Equals(a.y, b.y) && Equals(a.z, b.z) && Equals(a.w, b.w); }

constexpr float_t Calc::Lerp(const float_t value, const float_t target, const float_t time) { return value + (target - value) * time; }

constexpr float_t Calc::Lerp(const float_t value, const float_t target, const float_t time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

constexpr Vector2 Calc::Lerp(const Vector2 value, const Vector2 target, const float_t time) { return value + (target - value) * time; }

constexpr Vector2 Calc::Lerp(const Vector2 value, const Vector2 target, const float_t time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

constexpr Vector3 Calc::Lerp(const Vector3& value, const Vector3& target, const float_t time) { return value + (target - value) * time; }

constexpr Vector3 Calc::Lerp(const Vector3& value, const Vector3& target, const float_t time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

constexpr Vector4 Calc::Lerp(const Vector4& value, const Vector4& target, const float_t time) { return value + (target - value) * time; }

constexpr Vector4 Calc::Lerp(const Vector4& value, const Vector4& target, const float_t time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

#undef ZERO
