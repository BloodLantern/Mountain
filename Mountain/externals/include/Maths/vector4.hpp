#pragma once

#ifdef MATH_DEFINE_FORMATTER
#include <format>
#include <sstream>
#endif

#include <ostream>

#include "calc.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

/// @file vector4.hpp
/// @brief Defines the Vector4 class.

class Matrix;

/// @brief The Vector4 class represents either a four-dimensional vector or a point.
class MATH_TOOLBOX Vector4
{
public:
    /// @brief The @c x component of this Vector4.
    float_t x = 0.f;
    /// @brief The @c y component of this Vector4.
    float_t y = 0.f;
    /// @brief The @c z component of this Vector4.
    float_t z = 0.f;
    /// @brief The @c w component of this Vector4.
    float_t w = 0.f;

	/// @brief Equivalent to calling the default constructor.
	[[nodiscard]]
	static constexpr Vector4 Zero() noexcept;

	/// @brief Equivalent to calling the default constructor.
	static constexpr void Zero(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 1, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 0.
	[[nodiscard]]
	static constexpr Vector4 UnitX() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 1, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 0.
	static constexpr void UnitX(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 1, @c z @c = @c 0, @c w @c = @c 0.
	[[nodiscard]]
	static constexpr Vector4 UnitY() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 1, @c z @c = @c 0, @c w @c = @c 0.
	static constexpr void UnitY(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 1, @c w @c = @c 0.
	[[nodiscard]]
	static constexpr Vector4 UnitZ() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 1, @c w @c = @c 0.
	static constexpr void UnitZ(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 1.
	[[nodiscard]]
	static constexpr Vector4 UnitW() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 1.
	static constexpr void UnitW(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with all of its components set to @c 1.
	[[nodiscard]]
	static constexpr Vector4 One() noexcept;

    /// @brief Returns a Vector4 with all of its components set to @c 1.
	[[nodiscard]]
	static constexpr void One(Vector4* result) noexcept;

    /// @brief Constructs a Vector4 with everything set to @c 0.
	constexpr Vector4() = default;

	/// @brief Constructs a Vector4 with all its components set to @p xyzw.
	constexpr explicit Vector4(float_t xyzw) noexcept;
	
	/// @brief Constructs a Vector2 with its components set to the data pointed by @p data.
	/// 
	/// This constructor assumes that @p data is a valid pointer pointing to at least 2 @c float_t values.
	/// 
	/// @param data The data where the values for this vector's components are located.
	constexpr explicit Vector4(const float_t* data) noexcept;

	/// @brief Constructs a Vector3 with set component values.
	/// 
	/// @param x The value to set this vector's x components to.
	/// @param y The value to set this vector's y components to.
	/// @param z The value to set this vector's z components to.
	/// @param w The value to set this vector's w components to.
	constexpr Vector4(float_t x, float_t y, float_t z, float_t w) noexcept;

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
	
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	constexpr float_t SquaredLength() const noexcept;

	/// @brief Returns a normalized vector.
	/// 
	/// @returns A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector4 Normalized() const noexcept;

	/// @brief Returns a normalized vector.
	/// 
	/// @param result A vector to store the result which is one with the same direction but a length of one.
	void Normalized(Vector4* result) const noexcept;

	/// @brief Check whether all of this vector's components are infinite.
	[[nodiscard]]
	bool_t IsInfinity() const noexcept;

	/// @brief Check whether all of this vector's components are NaN.
	[[nodiscard]]
	bool_t IsNaN() const noexcept;

	/// @brief Returns a · b.
	[[nodiscard]]
	static constexpr float_t Dot(const Vector4& a, const Vector4& b) noexcept;

    /// @brief Clamps the given @p value between @p min and @p max.
    [[nodiscard]]
    static constexpr Vector4 Clamp(Vector4 value, Vector4 min, Vector4 max) noexcept;

	/// @brief Lerp between two positions in a 4-dimensional space.
	/// 
	/// @param value The current position.
	/// @param target The target position.
	/// @param t The time to lerp.
	/// @returns The lerp position.
	[[nodiscard]]
	static constexpr Vector4 Lerp(const Vector4& value, const Vector4& target, float_t t) noexcept;

	/// @brief Lerp between two positions in a 4-dimensional space.
	/// 
	/// @param value The current position.
	/// @param target The target position.
	/// @param t The time to lerp.
	/// @param result The lerp position.
	static constexpr void Lerp(const Vector4& value, const Vector4& target, float_t t, Vector4* result) noexcept;

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
	
    /// @brief Converts this Vector4 to a Vector2.
	explicit operator Vector2() const noexcept;

    /// @brief Converts this Vector4 to a Vector3.
    explicit operator Vector3() const noexcept;

    /// @brief Converts this Vector4 to an @ref Matrix::Identity "identity" Matrix with its first column vector set to this one.
	explicit operator Matrix() const noexcept;
};

static_assert(std::is_default_constructible_v<Vector4>, "Class Vector4 must be default constructible.");
static_assert(std::is_copy_constructible_v<Vector4>, "Class Vector4 must be copy constructible.");
static_assert(std::is_move_constructible_v<Vector4>, "Class Vector4 must be move constructible.");
static_assert(std::is_copy_assignable_v<Vector4>, "Class Vector4 must be copy assignable.");
static_assert(std::is_move_assignable_v<Vector4>, "Class Vector4 must be move assignable.");

constexpr Vector4::Vector4(const float_t xyzw) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

constexpr Vector4::Vector4(const float_t* const data) noexcept : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}

constexpr Vector4::Vector4(const float_t x, const float_t y, const float_t z, const float_t w) noexcept : x(x), y(y), z(z), w(w) {}

constexpr Vector4 Vector4::Zero() noexcept { return Vector4(); }

constexpr void Vector4::Zero(Vector4* result) noexcept { *result = Vector4(); }

constexpr Vector4 Vector4::UnitX() noexcept { return Vector4(1.f, 0.f, 0.f, 0.f); }

constexpr void Vector4::UnitX(Vector4* result) noexcept { *result = Vector4(1.f, 0.f, 0.f, 0.f); }

constexpr Vector4 Vector4::UnitY() noexcept { return Vector4(0.f, 1.f, 0.f, 0.f); }

constexpr void Vector4::UnitY(Vector4* result) noexcept { *result = Vector4(0.f, 1.f, 0.f, 0.f); }

constexpr Vector4 Vector4::UnitZ() noexcept { return Vector4(0.f, 0.f, 1.f, 0.f); }

constexpr void Vector4::UnitZ(Vector4* result) noexcept { *result = Vector4(0.f, 0.f, 1.f, 0.f); }

constexpr Vector4 Vector4::UnitW() noexcept { return Vector4(0.f, 0.f, 0.f, 1.f); }

constexpr void Vector4::UnitW(Vector4* result) noexcept { *result = Vector4(0.f, 0.f, 0.f, 1.f); }

constexpr Vector4 Vector4::One() noexcept { return Vector4(1); }

constexpr void Vector4::One(Vector4* result) noexcept { *result = Vector4(1); }

constexpr const float_t* Vector4::Raw() const noexcept { return &x; }

constexpr float_t* Vector4::Raw() noexcept { return &x; }

constexpr float_t Vector4::SquaredLength() const noexcept { return SQ(x) + SQ(y) + SQ(z) + SQ(w); }

constexpr float_t Vector4::Dot(const Vector4& a, const Vector4& b) noexcept {	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

constexpr Vector4 Vector4::Clamp(Vector4 value, Vector4 min, Vector4 max) noexcept
{
    return Vector4(std::clamp(value.x, min.x, max.x), std::clamp(value.y, min.y, max.y), std::clamp(value.z, min.z, max.z), std::clamp(value.w, min.w, max.w));
}

constexpr float_t Vector4::operator[](const size_t i) const
{
	if (i < 4) [[likely]]
		return *(Raw() + i);
	[[unlikely]]
		throw std::out_of_range("Vector4 subscript out of range");
}

constexpr float_t& Vector4::operator[](const size_t i)
{
	if (i < 4) [[likely]]
		return *(Raw() + i);
	[[unlikely]]
		throw std::out_of_range("Vector4 subscript out of range");
}

/// @brief Adds two Vector4 together.
[[nodiscard]]
constexpr Vector4 operator+(const Vector4& a, const Vector4& b) noexcept { return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

/// @brief Returns the opposite of a Vector4.
///
/// This effectively means replacing all values of this Vector4 with their opposite.
[[nodiscard]]
constexpr Vector4 operator-(const Vector4& a) noexcept { return Vector4(-a.x, -a.y, -a.z, -a.w); }

/// @brief Subtracts a Vector4 from another one.
[[nodiscard]]
constexpr Vector4 operator-(const Vector4& a, const Vector4& b) noexcept { return a + -b; }

/// @brief Multiplies two Vector4 component-wise.
[[nodiscard]]
constexpr Vector4 operator*(const Vector4& a, const Vector4& b) noexcept { return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }

/// @brief Multiplies a Vector4 by a @p factor.
[[nodiscard]]
constexpr Vector4 operator*(const Vector4& v, const float_t factor) noexcept { return Vector4(v.x * factor, v.y * factor, v.z * factor, v.w * factor); }

/// @brief Multiplies a Vector4 by a @p factor.
[[nodiscard]]
constexpr Vector4 operator*(const float_t factor, const Vector4 v) noexcept { return v * factor; }

/// @brief Divides a Vector4 by another one.
[[nodiscard]]
constexpr Vector4 operator/(const Vector4& a, const Vector4& b) noexcept { return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }

/// @brief Divides a Vector4 by a @p factor.
[[nodiscard]]
constexpr Vector4 operator/(const Vector4& v, const float_t factor) noexcept { const float_t invFactor = 1.f / factor; return Vector4(v.x * invFactor, v.y * invFactor, v.z * invFactor, v.w * invFactor); }

/// @brief Adds two Vector4 according to @ref operator+(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4& operator+=(Vector4& a, const Vector4& b) noexcept { return a = a + b; }

/// @brief Subtracts a Vector4 from another one according to @ref operator-(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4 &operator-=(Vector4 &a, const Vector4& b) noexcept { return a = a - b; }

/// @brief Multiplies two Vector4 component-wise according to @ref operator*(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4& operator*=(Vector4& a, const Vector4& b) noexcept { return a = a * b; }

/// @brief Multiplies a Vector4 by a @p factor according to @ref operator*(const Vector4&, const float_t), placing the result in @p v.
constexpr Vector4& operator*=(Vector4& v, const float_t factor) noexcept { return v = v * factor; }

/// @brief Divides two Vector4 component-wise according to @ref operator/(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4 &operator/=(Vector4 &a, const Vector4& b) noexcept { return a = a / b; }

/// @brief Divides a Vector4 by a @p factor according to @ref operator/(const Vector4&, const float_t), placing the result in @p v.
constexpr Vector4& operator/=(Vector4& v, const float_t factor) noexcept { return v = v / factor; }

/// @brief Checks if two Vector4 are considered equal using <code>Calc::Equals</code>.
[[nodiscard]]
constexpr bool_t operator==(const Vector4 a, const Vector4 b) noexcept
{
	return Calc::Equals(a.x, b.x)
		&& Calc::Equals(a.y, b.y)
		&& Calc::Equals(a.z, b.z)
		&& Calc::Equals(a.w, b.w);
}

/// @brief Checks if two Vector4 are considered different using <code>Calc::Equals</code>.
[[nodiscard]]
constexpr bool_t operator!=(const Vector4 a, const Vector4 b) noexcept { return !(a == b); }

/// @brief Streams a Vector4 into @p out, printing its values one by one on a single line.
MATH_TOOLBOX std::ostream& operator<<(std::ostream& out, const Vector4& v) noexcept;

constexpr Vector4 Vector4::Lerp(const Vector4& value, const Vector4& target, const float_t t) noexcept { return value + (target - value) * t; }

constexpr void Vector4::Lerp(const Vector4& value, const Vector4& target, const float_t t, Vector4* result) noexcept { *result = value + (target - value) * t; }

#ifdef MATH_DEFINE_FORMATTER
template <>
struct std::formatter<Vector4>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Vector4 v, FmtContext& ctx) const;

private:
    std::string m_Format;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Vector4, char_t>::parse(ParseContext& ctx)
{
    auto it = ctx.begin();
    if (it == ctx.end())
        return it;

    while (*it != '}' && it != ctx.end())
        m_Format += *it++;

    return it;
}

template <class FmtContext>
typename FmtContext::iterator std::formatter<Vector4>::format(Vector4 v, FmtContext &ctx) const
{
    std::ostringstream out;

    out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(v.x, v.y, v.z, v.w));

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
#endif
