#pragma once

#include <algorithm>
#include <numbers>

#include "Mountain/Math/Easing.hpp"
#include "Mountain/Math/Vector2.hpp"
#include "Mountain/Math/Vector3.hpp"
#include "Mountain/Math/Vector4.hpp"

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

struct Matrix2;
struct Matrix3;
struct Matrix;
struct Quaternion;
struct Vector2;
struct Vector3;
struct Vector4;

/// @namespace Calc
/// @brief This namespace contains mathematical constants and useful functions/macros.
namespace Calc
{
	/// @brief The value under which a number is considered to be zero.
	constexpr f32 Zero = ZERO;

	/// @brief Shorthand for writing @code std::numbers::pi_v<f32>@endcode.
	constexpr f32 Pi = std::numbers::pi_v<f32>;

	/// @brief Shorthand for writing @code Calc::Pi * 2.f@endcode.
	constexpr f32 TwoPi = Pi * 2.f;

	/// @brief Shorthand for writing @code Calc::Pi / 2.f@endcode.
	constexpr f32 PiOver2 = Pi / 2.f;

	/// @brief Shorthand for writing @code Calc::Pi / 4.f@endcode.
	constexpr f32 PiOver4 = Pi / 4.f;

	/// @brief Value used to convert from degrees to radians.
	constexpr f32 Deg2Rad = Pi / 180.f;

	/// @brief Value used to convert from radians to degrees.
	constexpr f32 Rad2Deg = 1.f / Deg2Rad;

	/// @brief Shorthand for writing @code std::numbers::sqrt_2<f32>@endcode.
	constexpr f32 Sqrt2 = std::numbers::sqrt2_v<f32>;

	/// @brief Shorthand for writing @code Sqrt2 / 2.f@endcode.
	constexpr f32 HalfSqrt2 = Sqrt2 / 2.f;

    /// @brief Returns -1 if x is less than 0, 1 if x is greater than 0 and 0 if x is equal to 0.
    ///
    /// @param number The number to get the sign of.
    /// @returns -1 if the value is negative, 1 if it is positive. 0 Otherwise.
    ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr f32 Sign(f32 number) noexcept;

	/// @brief	A constexpr version of the @c std::abs function.
	///
	/// @param number The number to get the absolute value of.
	/// @returns The absolute value of @p number.
	template <std::floating_point T>
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr T Abs(T number) noexcept;

	/// @brief	A constexpr version of the @c std::abs function for @c Vector2.
	///
	/// @param vector The vector to get the absolute value of.
	/// @returns A Vector2 whose components are the absolute values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector2 Abs(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the @c std::abs function for @c Vector3.
	///
	/// @param vector The vector to get the absolute value of.
	/// @returns A Vector3 whose components are the absolute values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector3 Abs(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the @c std::abs function for @c Vector4.
	///
	/// @param vector The vector to get the absolute value of.
	/// @returns A Vector4 whose components are the absolute values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector4 Abs(const Vector4& vector) noexcept;

	/// @brief	A constexpr version of the @c std::round function.
	///
	/// @param number The number to round to the nearest integer value.
	/// @returns The rounded value of @p number.
	template <std::floating_point T>
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr T Round(T number) noexcept;

	/// @brief	A constexpr version of the @c std::round function for @c Vector2.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector2 whose components are the rounded values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector2 Round(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the @c std::round function for @c Vector3.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector3 whose components are the rounded values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector3 Round(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the @c std::round function for @c Vector4.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector4 whose components are the rounded values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector4 Round(const Vector4& vector) noexcept;

    /// @brief	A constexpr version of the @c std::floor function.
    ///
    /// @param number The number to floor.
    /// @returns The floor value of @p number.
	template <std::floating_point T>
    ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr T Floor(T number) noexcept;

	/// @brief	A constexpr version of the @c std::floor function for @c Vector2.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector2 whose components are the floored values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector2 Floor(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the @c std::floor function for @c Vector3.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector3 whose components are the floored values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector3 Floor(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the @c std::floor function for @c Vector4.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector4 whose components are the floored values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector4 Floor(const Vector4& vector) noexcept;

    /// @brief	A constexpr version of the @c std::ceil function.
    ///
    /// @param number The number to ceil.
    /// @returns The ceil value of @p number.
	template <std::floating_point T>
    ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr T Ceil(T number) noexcept;

	/// @brief	A constexpr version of the @c std::ceil function for @c Vector2.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector2 whose components are the ceiled values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector2 Ceil(Vector2 vector) noexcept;

	/// @brief	A constexpr version of the @c std::ceil function for @c Vector3.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector3 whose components are the ceiled values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector3 Ceil(const Vector3& vector) noexcept;

	/// @brief	A constexpr version of the @c std::ceil function for @c Vector4.
	///
	/// @param vector The vector to round to the nearest integer value.
	/// @returns A Vector4 whose components are the ceiled values of @p vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector4 Ceil(const Vector4& vector) noexcept;

	/// @brief	A constexpr version of the @c std::clamp function.
	///
	/// @param number The number to clamp between two values.
	/// @param min The minimum value.
	/// @param max The maximum value.
	/// @returns The clamped number.
	template <std::floating_point T>
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr T Clamp(T number, T min, T max) noexcept;

	/// @brief	A constexpr version of the @c std::clamp function for @c Vector2.
	///
	/// @param vector The vector to clamp between two positions.
	/// @param min The minimum position.
	/// @param max The maximum position.
	/// @returns The clamped vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector2 Clamp(Vector2 vector, Vector2 min, Vector2 max) noexcept;

	/// @brief	A constexpr version of the @c std::clamp function for @c Vector3.
	///
	/// @param vector The vector to clamp between two positions.
	/// @param min The minimum position.
	/// @param max The maximum position.
	/// @returns The clamped vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector3 Clamp(const Vector3& vector, const Vector3& min, const Vector3& max) noexcept;

	/// @brief	A constexpr version of the @c std::clamp function for @c Vector4.
	///
	/// @param vector The vector to clamp between two positions.
	/// @param min The minimum position.
	/// @param max The maximum position.
	/// @returns The clamped vector.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr Vector4 Clamp(const Vector4& vector, const Vector4& min, const Vector4& max) noexcept;

	/// @brief	A constexpr version of the @c std::fmodf function.
	///
	/// @param a The left-hand side of the modulo.
	/// @param b The right-hand side of the modulo.
	/// @returns The modulo of @p a by @p b.
	template <std::floating_point T>
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr T Modulo(T a, T b) noexcept;

	/// @brief	A constexpr version of the @c std::isnan function.
	///
	/// @param value The floating-point value to check.
	/// @returns @c true if @p value is NaN, @c false otherwise.
	template <std::floating_point T>
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr bool IsNan(T value) noexcept;

	/// @brief Approaches the target value by the given step size without ever exceeding it.
	///
	/// @param value The value to change.
	/// @param target The target value.
	/// @param step The step size.
	MOUNTAIN_API constexpr void Approach(f32& value, f32 target, f32 step) noexcept;

	/// @brief Approaches the target value by the given step size without ever exceeding it.
	///
	/// @param value The value to change.
	/// @param target The target value.
	/// @param step The step size.
	MOUNTAIN_API constexpr void Approach(Vector2& value, Vector2 target, Vector2 step) noexcept;

	/// @brief Approaches the target value by the given step size without ever exceeding it.
	///
	/// @param value The value to change.
	/// @param target The target value.
	/// @param step The step size.
	MOUNTAIN_API constexpr void Approach(Vector3& value, Vector3 target, Vector3 step) noexcept;

	/// @brief Approaches the target value by the given step size without ever exceeding it.
	///
	/// @param value The value to change.
	/// @param target The target value.
	/// @param step The step size.
	MOUNTAIN_API constexpr void Approach(Vector4& value, Vector4 target, Vector4 step) noexcept;

	/// @brief Given a value between 0 and 1, returns a value going from 0 to 1 and to 0 again.
	///
	/// @param value The YoYo value.
	/// @returns A value between 0 and 1, closer to 1 if the input value is close to 0.5.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr f32 YoYo(f32 value) noexcept;

	/// @brief Returns true on an interval.
	///
	/// @param value The current time value.
	/// @param lastValue The last time value. (last call)
	/// @param interval The interval.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr bool OnInterval(f32 value, f32 lastValue, f32 interval);

	/// @brief Clamps the given @p value between @p min and @p max and remaps the result between @p newMin and @p newMax
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr f32 ClampedMap(
		f32 value,
		f32 min,
		f32 max,
		f32 newMin = 0.f,
		f32 newMax = 1.f
	);

    /// @brief Checks if a value is less than what is considered to be zero, e.g. if its absolute value is smaller than @c Calc::Zero.
    ///
    /// @param value The value to check.
    /// @returns Whether the value is considered to be zero.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr bool IsZero(f32 value) noexcept;

    /// @brief Checks if a value is less than what is considered to be zero, e.g. if its absolute value is smaller than @p zero.
    ///
    /// @param value The value to check.
    /// @param zero The value under which a number is considered to be zero.
    /// @returns Whether the value is considered to be zero.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr bool IsZero(f32 value, f32 zero) noexcept;

    /// @brief If a value is considered zero using @c IsZero(), returns 0. Otherwise, returns the given value.
    ///
    /// @param value The value to check.
    /// @returns Whether the value is considered to be zero.
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API constexpr f32 MakeZero(f32 value) noexcept;

    /// @brief If a value is considered zero using @c IsZero(), returns 0. Otherwise, returns the given value.
    ///
    /// @param value The value to check.
    /// @param zero The value under which a number is considered to be zero.
    /// @returns Whether the value is considered to be zero.
    ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr f32 MakeZero(f32 value, f32 zero) noexcept;

	/// @brief Checks if two values are considered equal using @ref IsZero(f32).
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr bool Equals(f32 a, f32 b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr bool Equals(Vector2 a, Vector2 b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr bool Equals(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API constexpr bool Equals(const Vector4& a, const Vector4& b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API bool Equals(const Matrix2& a, const Matrix2& b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API bool Equals(const Matrix3& a, const Matrix3& b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API bool Equals(const Matrix& a, const Matrix& b) noexcept;

	/// @brief Checks if two values are considered equal using @c IsZero().
	///
	/// @param a The first value.
	/// @param b The second value.
	/// @returns Whether the values are considered equal.
	ATTRIBUTE_NODISCARD
	MOUNTAIN_API bool Equals(const Quaternion& a, const Quaternion& b) noexcept;

	ATTRIBUTE_NODISCARD
	constexpr f32 Lerp(f32 value, f32 target, f32 time);

	ATTRIBUTE_NODISCARD
	constexpr f32 Lerp(f32 value, f32 target, f32 time, Easing::Easer easer);

	ATTRIBUTE_NODISCARD
	constexpr Vector2 Lerp(Vector2 value, Vector2 target, f32 time);

	ATTRIBUTE_NODISCARD
	constexpr Vector2 Lerp(Vector2 value, Vector2 target, f32 time, Easing::Easer easer);

	ATTRIBUTE_NODISCARD
	constexpr Vector3 Lerp(const Vector3& value, const Vector3& target, f32 time);

	ATTRIBUTE_NODISCARD
	constexpr Vector3 Lerp(const Vector3& value, const Vector3& target, f32 time, Easing::Easer easer);

	ATTRIBUTE_NODISCARD
	constexpr Vector4 Lerp(const Vector4& value, const Vector4& target, f32 time);

	ATTRIBUTE_NODISCARD
	constexpr Vector4 Lerp(const Vector4& value, const Vector4& target, f32 time, Easing::Easer easer);
}

constexpr f32 Calc::Sign(const f32 number) noexcept { if (IsZero(number)) return 0.f; return number < 0.f ? -1.f : 1.f; }

template <std::floating_point T>
constexpr T Calc::Abs(T number) noexcept { return number < 0.f ? -number : number; }

constexpr Vector2 Calc::Abs(const Vector2 vector) noexcept { return { Abs(vector.x), Abs(vector.y) }; }

constexpr Vector3 Calc::Abs(const Vector3& vector) noexcept { return { Abs(vector.x), Abs(vector.y), Abs(vector.z) }; }

constexpr Vector4 Calc::Abs(const Vector4& vector) noexcept { return { Abs(vector.x), Abs(vector.y), Abs(vector.z), Abs(vector.w) }; }

template <std::floating_point T>
constexpr T Calc::Round(T number) noexcept
{
	const s32 lower = static_cast<s32>(number);
	const s32 upper = static_cast<s32>(number + 0.5f);  // NOLINT(bugprone-incorrect-roundings)

	return static_cast<f32>(lower < upper ? upper : lower);
}

constexpr Vector2 Calc::Round(const Vector2 vector) noexcept { return { Round(vector.x), Round(vector.y) }; }

constexpr Vector3 Calc::Round(const Vector3& vector) noexcept { return { Round(vector.x), Round(vector.y), Round(vector.z) }; }

constexpr Vector4 Calc::Round(const Vector4& vector) noexcept { return { Round(vector.x), Round(vector.y), Round(vector.z), Round(vector.w) }; }

template <std::floating_point T>
constexpr T Calc::Floor(T number) noexcept { return Round(number - 0.5f); }

constexpr Vector2 Calc::Floor(const Vector2 vector) noexcept { return { Floor(vector.x), Floor(vector.y) }; }

constexpr Vector3 Calc::Floor(const Vector3& vector) noexcept { return { Floor(vector.x), Floor(vector.y), Floor(vector.z) }; }

constexpr Vector4 Calc::Floor(const Vector4& vector) noexcept { return { Floor(vector.x), Floor(vector.y), Floor(vector.z), Floor(vector.w) }; }

template <std::floating_point T>
constexpr T Calc::Ceil(T number) noexcept { return Round(number + 0.5f); }

constexpr Vector2 Calc::Ceil(const Vector2 vector) noexcept { return { Ceil(vector.x), Ceil(vector.y) }; }

constexpr Vector3 Calc::Ceil(const Vector3& vector) noexcept { return { Ceil(vector.x), Ceil(vector.y), Ceil(vector.z) }; }

constexpr Vector4 Calc::Ceil(const Vector4& vector) noexcept { return { Ceil(vector.x), Ceil(vector.y), Ceil(vector.z), Ceil(vector.w) }; }

template <std::floating_point T>
constexpr T Calc::Clamp(T number, T min, T max) noexcept
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

template <std::floating_point T>
constexpr T Calc::Modulo(T a, T b) noexcept { return a - static_cast<f32>(static_cast<s64>(a / b)) * b; }

template <std::floating_point T>
constexpr bool Calc::IsNan(T value) noexcept
{
	return std::isnan(value);
}

// Undef windows macro to be able to use std::min without conflicts
#undef min

constexpr void Calc::Approach(f32 &value, const f32 target, const f32 step) noexcept
{
	// If the target value hasn't been reached yet
	if (!Equals(value, target))
	{
		const f32 difference = target - value;
		value += std::min(step, Abs(difference)) * Sign(difference);
	}
}

constexpr void Calc::Approach(Vector2& value, const Vector2 target, const Vector2 step) noexcept
{
	Approach(value.x, target.x, step.x);
	Approach(value.y, target.y, step.y);
}

constexpr void Calc::Approach(Vector3& value, const Vector3 target, const Vector3 step) noexcept
{
	Approach(value.x, target.x, step.x);
	Approach(value.y, target.y, step.y);
	Approach(value.z, target.z, step.z);
}

constexpr void Calc::Approach(Vector4& value, const Vector4 target, const Vector4 step) noexcept
{
	Approach(value.x, target.x, step.x);
	Approach(value.y, target.y, step.y);
	Approach(value.z, target.z, step.z);
	Approach(value.w, target.w, step.w);
}

constexpr f32 Calc::YoYo(const f32 value) noexcept { return value <= 0.5f ? value * 2.f : 1.f - (value - 0.5f) * 2.f; }

constexpr bool Calc::OnInterval(const f32 value, const f32 lastValue, const f32 interval)
{
	return IsZero(interval) || static_cast<s32>(lastValue / interval) != static_cast<s32>(value / interval);
}

constexpr f32 Calc::ClampedMap(const f32 value, const f32 min, const f32 max, const f32 newMin, const f32 newMax)
{
	return Clamp((value - min) / (max - min), 0.f, 1.f) * (newMax - newMin) + newMin;
}

constexpr bool Calc::IsZero(const f32 value) noexcept { return IsZero(value, Zero); }

constexpr bool Calc::IsZero(const f32 value, const f32 zero) noexcept { return Abs(value) <= zero; }

constexpr f32 Calc::MakeZero(const f32 value) noexcept { return MakeZero(value, Zero); }

constexpr f32 Calc::MakeZero(const f32 value, const f32 zero) noexcept { return IsZero(value, zero) ? 0.f : value; }

constexpr bool Calc::Equals(const f32 a, const f32 b) noexcept { return IsZero(a - b); }

constexpr bool Calc::Equals(const Vector2 a, const Vector2 b) noexcept { return Equals(a.x, b.x) && Equals(a.y, b.y); }

constexpr bool Calc::Equals(const Vector3& a, const Vector3& b) noexcept { return Equals(a.x, b.x) && Equals(a.y, b.y) && Equals(a.z, b.z); }

constexpr bool Calc::Equals(const Vector4& a, const Vector4& b) noexcept { return Equals(a.x, b.x) && Equals(a.y, b.y) && Equals(a.z, b.z) && Equals(a.w, b.w); }

constexpr f32 Calc::Lerp(const f32 value, const f32 target, const f32 time) { return value + (target - value) * time; }

constexpr f32 Calc::Lerp(const f32 value, const f32 target, const f32 time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

constexpr Vector2 Calc::Lerp(const Vector2 value, const Vector2 target, const f32 time) { return value + (target - value) * time; }

constexpr Vector2 Calc::Lerp(const Vector2 value, const Vector2 target, const f32 time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

constexpr Vector3 Calc::Lerp(const Vector3& value, const Vector3& target, const f32 time) { return value + (target - value) * time; }

constexpr Vector3 Calc::Lerp(const Vector3& value, const Vector3& target, const f32 time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

constexpr Vector4 Calc::Lerp(const Vector4& value, const Vector4& target, const f32 time) { return value + (target - value) * time; }

constexpr Vector4 Calc::Lerp(const Vector4& value, const Vector4& target, const f32 time, const Easing::Easer easer)
{
	return value + (target - value) * easer(time);
}

#undef ZERO
