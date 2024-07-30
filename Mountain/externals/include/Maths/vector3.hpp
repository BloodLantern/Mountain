#pragma once

#ifdef MATH_DEFINE_FORMATTER
#include <format>
#include <sstream>
#endif

#include <ostream>

#include "Maths/calc.hpp"
#include "Maths/vector2.hpp"

/// @file vector3.hpp
/// @brief Defines the Vector3 class.

class Vector4;
class Matrix;

/// @brief The Vector3 class represents either a three-dimensional vector or a point.
class MATH_TOOLBOX Vector3
{
public:
    /// @brief The @c x component of this Vector3.
    float_t x = 0.f;
    
    /// @brief The @c y component of this Vector3.
    float_t y = 0.f;
    
    /// @brief The @c z component of this Vector3.
    float_t z = 0.f;

	/// @brief Equivalent to calling the default constructor.
	[[nodiscard]]
	static constexpr Vector3 Zero() noexcept;

	/// @brief Equivalent to calling the default constructor.
	static constexpr void Zero(Vector3* result) noexcept;

    /// @brief Returns a Vector3 with @c x @c = @c 1, @c y @c = @c 0, @c z @c = @c 0.
	[[nodiscard]]
	static constexpr Vector3 UnitX() noexcept;

    /// @brief Returns a Vector3 with @c x @c = @c 1, @c y @c = @c 0, @c z @c = @c 0.
	static constexpr void UnitX(Vector3* result) noexcept;

    /// @brief Returns a Vector3 with @c x @c = @c 0, @c y @c = @c 1, @c z @c = @c 0.
	[[nodiscard]]
	static constexpr Vector3 UnitY() noexcept;

    /// @brief Returns a Vector3 with @c x @c = @c 0, @c y @c = @c 1, @c z @c = @c 0.
	static constexpr void UnitY(Vector3* result) noexcept;

    /// @brief Returns a Vector3 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 1.
	[[nodiscard]]
	static constexpr Vector3 UnitZ() noexcept;

    /// @brief Returns a Vector3 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 1.
	static constexpr void UnitZ(Vector3* result) noexcept;

    /// @brief Returns a Vector3 with all of its components set to @c 1.
	[[nodiscard]]
	static constexpr Vector3 One() noexcept;

    /// @brief Returns a Vector3 with all of its components set to @c 1.
	[[nodiscard]]
	static constexpr void One(Vector3* result) noexcept;

	/// @brief Returns a · b.
	[[nodiscard]]
	static constexpr float_t Dot(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Returns a x b.
	[[nodiscard]]
	static constexpr Vector3 Cross(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Returns a x b.
	static constexpr void Cross(const Vector3& a, const Vector3& b, Vector3* result) noexcept;

    /// @brief Clamps the given @p value between @p min and @p max.
    [[nodiscard]]
    static constexpr Vector3 Clamp(Vector3 value, Vector3 min, Vector3 max) noexcept;

	/// @brief Lerp between two positions in a 3-dimensional space.
	/// 
	/// @param value The current position.
	/// @param target The target position.
	/// @param t The time to lerp.
	/// @returns The lerp position.
	[[nodiscard]]
	static constexpr Vector3 Lerp(const Vector3& value, const Vector3& target, float_t t) noexcept;

	/// @brief Lerp between two positions in a 3-dimensional space.
	/// 
	/// @param value The current position.
	/// @param target The target position.
	/// @param t The time to lerp.
	/// @param result The lerp position.
	static constexpr void Lerp(const Vector3& value, const Vector3& target, float_t t, Vector3* result) noexcept;

    /// @brief Combines 2 Vector3
    /// @param a First vector
    /// @param b Second vector
    /// @param aScale First vector scale
    /// @param bScale Second vector scale
    /// @result Result
    [[nodiscard]]
    constexpr static Vector3 Combine(const Vector3& a, const Vector3& b, float_t aScale, float_t bScale) noexcept;

	/// @brief Constructs a Vector3 with both its components set to 0.
	constexpr Vector3() = default;
	
	/// @brief Constructs a Vector3 with both its components set to @p xyz.
	/// 
	/// @param xyz The value to set this vector's x, y and z components to.
	constexpr explicit Vector3(float_t xyz) noexcept;
	
	/// @brief Constructs a Vector2 with its components set to the data pointed by @p data.
	/// 
	/// This constructor assumes that @p data is a valid pointer pointing to at least 2 @c float_t values.
	/// 
	/// @param data The data where the values for this vector's components are located.
	constexpr explicit Vector3(const float_t* data) noexcept;

	/// @brief Constructs a Vector3 with set component values.
	/// 
	/// @param x The value to set this vector's x components to.
	/// @param y The value to set this vector's y components to.
	/// @param z The value to set this vector's z components to.
	constexpr Vector3(float_t x, float_t y, float_t z) noexcept;

	/// @brief Gets a pointer to the first component of this vector.
	/// 
	/// @returns A pointer to the first component of this vector.
	[[nodiscard]]
	constexpr const float_t* Raw() const noexcept;

	/// @brief Gets a pointer to the first component of this vector.
	/// 
	/// @returns A pointer to the first component of this vector.
	[[nodiscard]]
	constexpr float_t* Raw() noexcept;

	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float_t Length() const noexcept;

    /// @brief Creates a rescaled version of this Vector3.
    ///
    /// @param newLength The new length to give to the Vector3.
    ///
    /// @see Length
    [[nodiscard]]
    Vector3 Rescaled(float_t newLength) noexcept;
	
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	constexpr float_t SquaredLength() const noexcept;

	/// @brief Returns a normalized vector.
	/// 
	/// @returns A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector3 Normalized() const noexcept;

	/// @brief Returns a normalized vector.
	/// 
	/// @param result A vector to store the result which is one with the same direction but a length of one.
	void Normalized(Vector3* result) const noexcept;

	/// @brief Check whether all of this vector's components are infinite.
	[[nodiscard]]
	bool_t IsInfinity() const noexcept;

	/// @brief Check whether all of this vector's components are NaN.
	[[nodiscard]]
	bool_t IsNaN() const noexcept;

	/// @brief Retrieves this vector's component at index i.
	///
	/// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
	/// 
	/// @returns The value of the component at index i.
	[[nodiscard]]
	constexpr float_t operator[](size_t i) const;

	/// @brief Retrieves this vector's component at index i.
	///
	/// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
	/// 
	/// @returns The value of the component at index i.
	[[nodiscard]]
	constexpr float_t& operator[](size_t i);
	
    /// @brief Converts this Vector3 to a Vector2.
    explicit operator Vector2() const noexcept;

    /// @brief Converts this Vector3 to a Vector4 by giving it a @c z value of @c 0 and a @c w value of @c 1.
	explicit operator Vector4() const noexcept;
};

static_assert(std::is_default_constructible_v<Vector3>, "Class Vector3 must be default constructible.");
static_assert(std::is_copy_constructible_v<Vector3>, "Class Vector3 must be copy constructible.");
static_assert(std::is_move_constructible_v<Vector3>, "Class Vector3 must be move constructible.");
static_assert(std::is_copy_assignable_v<Vector3>, "Class Vector3 must be copy assignable.");
static_assert(std::is_move_assignable_v<Vector3>, "Class Vector3 must be move assignable.");

constexpr Vector3::Vector3(const float_t xyz) noexcept : x(xyz), y(xyz), z(xyz) {}

constexpr Vector3::Vector3(const float_t* const data) noexcept : x(data[0]), y(data[1]), z(data[2]) {}

constexpr Vector3::Vector3(const float_t x, const float_t y, const float_t z) noexcept : x(x), y(y), z(z) {}

constexpr Vector3 Vector3::Zero() noexcept { return Vector3(); }

constexpr void Vector3::Zero(Vector3* result) noexcept { *result = Vector3(); }

constexpr Vector3 Vector3::UnitX() noexcept { return Vector3(1.f, 0.f, 0.f); }

constexpr void Vector3::UnitX(Vector3* result) noexcept { *result = Vector3(1.f, 0.f, 0.f); }

constexpr Vector3 Vector3::UnitY() noexcept { return Vector3(0.f, 1.f, 0.f); }

constexpr void Vector3::UnitY(Vector3* result) noexcept { *result = Vector3(0.f, 1.f, 0.f); }

constexpr Vector3 Vector3::UnitZ() noexcept { return Vector3(0.f, 0.f, 1.f); }

constexpr void Vector3::UnitZ(Vector3* result) noexcept { *result = Vector3(0.f, 0.f, 1.f); }

constexpr Vector3 Vector3::One() noexcept { return Vector3(1); }

constexpr void Vector3::One(Vector3* result) noexcept { *result = Vector3(1); }

constexpr float_t Vector3::Dot(const Vector3& a, const Vector3& b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }

constexpr Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

constexpr void Vector3::Cross(const Vector3& a, const Vector3& b, Vector3* result) noexcept { *result = Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

constexpr Vector3 Vector3::Clamp(Vector3 value, Vector3 min, Vector3 max) noexcept
{
    return Vector3(std::clamp(value.x, min.x, max.x), std::clamp(value.y, min.y, max.y), std::clamp(value.z, min.z, max.z));
}

constexpr const float_t* Vector3::Raw() const noexcept { return &x; }

constexpr float_t* Vector3::Raw() noexcept { return &x; }

constexpr float_t Vector3::SquaredLength() const noexcept { return SQ(x) + SQ(y) + SQ(z); }

constexpr float_t Vector3::operator[](const size_t i) const
{
	if (i < 3) [[likely]]
		return *(Raw() + i);
	[[unlikely]]
	throw std::out_of_range("Vector3 subscript out of range");
}

constexpr float_t& Vector3::operator[](const size_t i)
{
	if (i < 3) [[likely]]
		return *(Raw() + i);
	[[unlikely]]
	throw std::out_of_range("Vector3 subscript out of range");
}

/// @brief Adds two Vector3 together.
[[nodiscard]]
constexpr Vector3 operator+(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }

/// @brief Returns the opposite of a Vector3.
///
/// This effectively means replacing all values of this Vector3 with their opposite.
[[nodiscard]]
constexpr Vector3 operator-(const Vector3& a) noexcept { return Vector3(-a.x, -a.y, -a.z); }

/// @brief Subtracts a Vector3 from another one.
[[nodiscard]]
constexpr Vector3 operator-(const Vector3& a, const Vector3& b) noexcept { return a + -b; }

/// @brief Multiplies two Vector3 component-wise.
[[nodiscard]]
constexpr Vector3 operator*(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.x * b.x, a.y * b.y, a.z * b.z); }

/// @brief Multiplies a Vector3 by a @p factor.
[[nodiscard]]
constexpr Vector3 operator*(const Vector3& v, const float_t factor) noexcept { return Vector3(v.x * factor, v.y * factor, v.z * factor); }

/// @brief Multiplies a Vector3 by a @p factor.
[[nodiscard]]
constexpr Vector3 operator*(const float_t factor, const Vector3 v) noexcept { return v * factor; }

/// @brief Divides a Vector3 by another one.
[[nodiscard]]
constexpr Vector3 operator/(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.x / b.x, a.y / b.y, a.z / b.z); }

/// @brief Divides a Vector3 by a @p factor.
[[nodiscard]]
constexpr Vector3 operator/(const Vector3& v, const float_t factor) noexcept { const float_t invFactor = 1.f / factor; return Vector3(v.x * invFactor, v.y * invFactor, v.z * invFactor); }

/// @brief Adds two Vector3 according to @ref operator+(const Vector3&, const Vector3&), placing the result in @p a.
constexpr Vector3& operator+=(Vector3& a, const Vector3& b) noexcept { return a = a + b; }

/// @brief Subtracts a Vector3 from another one according to @ref operator-(const Vector3&, const Vector3&), placing the result in @p a.
constexpr Vector3 &operator-=(Vector3 &a, const Vector3& b) noexcept { return a = a - b; }

/// @brief Multiplies two Vector3 component-wise according to @ref operator*(const Vector3&, const Vector3&), placing the result in @p a.
constexpr Vector3& operator*=(Vector3& a, const Vector3& b) noexcept { return a = a * b; }

/// @brief Multiplies a Vector3 by a @p factor according to @ref operator*(const Vector3&, const float_t), placing the result in @p v.
constexpr Vector3& operator*=(Vector3& v, const float_t factor) noexcept { return v = v * factor; }

/// @brief Divides two Vector3 component-wise according to @ref operator/(const Vector3&, const Vector3&), placing the result in @p a.
constexpr Vector3 &operator/=(Vector3 &a, const Vector3& b) noexcept { return a = a / b; }

/// @brief Divides a Vector3 by a @p factor according to @ref operator/(const Vector3&, const float_t), placing the result in @p v.
constexpr Vector3& operator/=(Vector3& v, const float_t factor) noexcept { return v = v / factor; }

/// @brief Checks if two Vector3 are considered equal using @ref Calc::Equals.
[[nodiscard]]
constexpr bool_t operator==(const Vector3 a, const Vector3 b) noexcept
{
	return Calc::Equals(a.x, b.x)
		&& Calc::Equals(a.y, b.y)
		&& Calc::Equals(a.z, b.z);
}

/// @brief Checks if two Vector3 are considered different using @ref Calc::Equals.
[[nodiscard]]
constexpr bool_t operator!=(const Vector3 a, const Vector3 b) noexcept { return !(a == b); }

/// @brief Streams a Vector3 into @p out, printing its values one by one on a single line.
MATH_TOOLBOX std::ostream& operator<<(std::ostream& out, const Vector3& v) noexcept;

constexpr Vector3 Vector3::Lerp(const Vector3& value, const Vector3& target, const float_t t) noexcept { return value + (target - value) * t; }

constexpr void Vector3::Lerp(const Vector3& value, const Vector3& target, const float_t t, Vector3* result) noexcept { *result = value + (target - value) * t; }

constexpr Vector3 Vector3::Combine(const Vector3& a, const Vector3& b, const float_t aScale, const float_t bScale) noexcept { return (a * aScale) + (b * bScale); }

#ifdef MATH_DEFINE_FORMATTER
template <>
struct std::formatter<Vector3>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Vector3 v, FmtContext& ctx) const;

private:
    std::string m_Format;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Vector3, char_t>::parse(ParseContext& ctx)
{
    auto it = ctx.begin();
    if (it == ctx.end())
        return it;

    while (*it != '}' && it != ctx.end())
        m_Format += *it++;

    return it;
}

template <class FmtContext>
typename FmtContext::iterator std::formatter<Vector3>::format(Vector3 v, FmtContext &ctx) const
{
    std::ostringstream out;

    out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(v.x, v.y, v.z));

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
#endif
