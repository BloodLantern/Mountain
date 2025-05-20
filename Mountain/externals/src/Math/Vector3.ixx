module;

#include "Math/Core.hpp"

export module Math:Vector3;

import std;
import :Types;
import :Forward;
import :Vector2;

/// @file Vector3.ixx
/// @brief Defines the Vector3 struct.

/// @brief The Vector3 struct represents either a three-dimensional vector or a point.
export struct MATH_API Vector3
{
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
	static constexpr void One(Vector3* result) noexcept;

	/// @brief Returns @p a · @p b.
	[[nodiscard]]
	static constexpr float_t Dot(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Returns @p a x @p b.
	[[nodiscard]]
	static constexpr Vector3 Cross(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Returns @p a x @p b.
	static constexpr void Cross(const Vector3& a, const Vector3& b, Vector3* result) noexcept;

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

    // ReSharper disable once CppNonExplicitConvertingConstructor
	/// @brief Constructs a Vector3 with both its components set to @p xyz.
	///
	/// @param xyz The value to set this vector's x, y and z components to.
    explicit constexpr Vector3(float_t xyz) noexcept;

	/// @brief Constructs a Vector2 with its components set to the data pointed by @p data.
	///
	/// This constructor assumes that @p data is a valid pointer pointing to at least three @c float_t values.
	///
	/// @param data The data where the values for this vector's components are located.
	constexpr explicit Vector3(const float_t* data) noexcept;

	/// @brief Constructs a Vector3 with set component values.
	///
	/// @param x The value to set this vector's x to.
	/// @param y The value to set this vector's y to.
	/// @param z The value to set this vector's z to.
	constexpr Vector3(float_t x, float_t y, float_t z) noexcept;

	/// @brief Gets a pointer to the first component of this vector.
	///
	/// @returns A pointer to the first component of this vector.
	[[nodiscard]]
	constexpr const float_t* Data() const noexcept;

	/// @brief Gets a pointer to the first component of this vector.
	///
	/// @returns A pointer to the first component of this vector.
	[[nodiscard]]
	constexpr float_t* Data() noexcept;

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

	/// @brief Retrieves this vector's component at index @p i.
	///
	/// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
	///
	/// @returns The value of the component at index @p i.
	[[nodiscard]]
	constexpr float_t& operator[](size_t i);

    /// @brief Converts this @c Vector3 to a @c Vector2.
    explicit operator Vector2() const noexcept;

    /// @brief Converts this @c Vector3 to a @c Vector4 by giving it a @c w value of @c 1.
	explicit operator Vector4() const noexcept;

	/// @brief Adds two Vector3 together.
	constexpr friend Vector3 operator+(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Returns the opposite of a Vector3.
	constexpr friend Vector3 operator-(const Vector3& a) noexcept;

	/// @brief Subtracts a Vector3 from another one.
	constexpr friend Vector3 operator-(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Multiplies two Vector3 component-wise.
	constexpr friend Vector3 operator*(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Multiplies a Vector3 by a @p factor.
	constexpr friend Vector3 operator*(const Vector3& v, float_t factor) noexcept;

	/// @brief Multiplies a Vector3 by a @p factor.
	constexpr friend Vector3 operator*(float_t factor, Vector3 v) noexcept;

	/// @brief Divides a Vector3 by another one.
	constexpr friend Vector3 operator/(const Vector3& a, const Vector3& b) noexcept;

	/// @brief Divides a Vector3 by a @p factor.
	constexpr friend Vector3 operator/(const Vector3& v, float_t factor) noexcept;

	/// @brief Adds two Vector3 according to @c operator+(const Vector3&, const Vector3&), placing the result in @p a.
	constexpr friend Vector3& operator+=(Vector3& a, const Vector3& b) noexcept;

	/// @brief Subtracts a Vector3 from another one according to @c operator-(const Vector3&, const Vector3&), placing the result in @p a.
	constexpr friend Vector3 &operator-=(Vector3 &a, const Vector3& b) noexcept;

	/// @brief Multiplies two Vector3 component-wise, according to @c operator*(const Vector3&, const Vector3&), placing the result in @p a.
	constexpr friend Vector3& operator*=(Vector3& a, const Vector3& b) noexcept;

	/// @brief Multiplies a Vector3 by a @p factor according to @c operator*(const Vector3&, const float_t), placing the result in @p v.
	constexpr friend Vector3& operator*=(Vector3& v, float_t factor) noexcept;

	/// @brief Divides two Vector3 component-wise, according to @c operator/(const Vector3&, const Vector3&), placing the result in @p a.
	constexpr friend Vector3 &operator/=(Vector3 &a, const Vector3& b) noexcept;

	/// @brief Divides a Vector3 by a @p factor according to @c operator/(const Vector3&, const float_t), placing the result in @p v.
	constexpr friend Vector3& operator/=(Vector3& v, float_t factor) noexcept;

	/// @brief Checks if two Vector3 are equal.
	constexpr friend bool_t operator==(Vector3 a, Vector3 b) noexcept;

	/// @brief Checks if two Vector3 are different.
	constexpr friend bool_t operator!=(Vector3 a, Vector3 b) noexcept;

	/// @brief Streams a Vector3 into @p out, printing its values one by one on a single line.
	friend std::ostream& operator<<(std::ostream& out, const Vector3& v) noexcept;
};

static_assert(std::is_default_constructible_v<Vector3>, "Struct Vector3 must be default constructible.");
static_assert(std::is_copy_constructible_v<Vector3>, "Struct Vector3 must be copy constructible.");
static_assert(std::is_move_constructible_v<Vector3>, "Struct Vector3 must be move constructible.");
static_assert(std::is_copy_assignable_v<Vector3>, "Struct Vector3 must be copy assignable.");
static_assert(std::is_move_assignable_v<Vector3>, "Struct Vector3 must be move assignable.");

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

constexpr Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) noexcept
{
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

constexpr void Vector3::Cross(const Vector3& a, const Vector3& b, Vector3* result) noexcept
{
	*result = Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

constexpr Vector3 Vector3::Combine(const Vector3& a, const Vector3& b, const float_t aScale, const float_t bScale) noexcept
{
	return a * aScale + b * bScale;
}

constexpr const float_t* Vector3::Data() const noexcept { return &x; }

constexpr float_t* Vector3::Data() noexcept { return &x; }

constexpr float_t Vector3::SquaredLength() const noexcept { return SQ(x) + SQ(y) + SQ(z); }

constexpr float_t Vector3::operator[](const size_t i) const
{
	if (i < 3) [[likely]]
		return *(Data() + i);
	[[unlikely]]
	throw std::out_of_range("Vector3 subscript out of range");
}

constexpr float_t& Vector3::operator[](const size_t i)
{
	if (i < 3) [[likely]]
		return *(Data() + i);
	[[unlikely]]
	throw std::out_of_range("Vector3 subscript out of range");
}

export [[nodiscard]] constexpr Vector3 operator+(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }

export [[nodiscard]] constexpr Vector3 operator-(const Vector3& a) noexcept { return Vector3(-a.x, -a.y, -a.z); }

export [[nodiscard]] constexpr Vector3 operator-(const Vector3& a, const Vector3& b) noexcept { return a + -b; }

export [[nodiscard]] constexpr Vector3 operator*(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.x * b.x, a.y * b.y, a.z * b.z); }

export [[nodiscard]] constexpr Vector3 operator*(const Vector3& v, const float_t factor) noexcept { return Vector3(v.x * factor, v.y * factor, v.z * factor); }

export [[nodiscard]] constexpr Vector3 operator*(const float_t factor, const Vector3 v) noexcept { return v * factor; }

export [[nodiscard]] constexpr Vector3 operator/(const Vector3& a, const Vector3& b) noexcept { return Vector3(a.x / b.x, a.y / b.y, a.z / b.z); }

export [[nodiscard]] constexpr Vector3 operator/(const Vector3& v, const float_t factor) noexcept
{
	const float_t invFactor = 1.f / factor;
	return Vector3(v.x * invFactor, v.y * invFactor, v.z * invFactor);
}

export constexpr Vector3& operator+=(Vector3& a, const Vector3& b) noexcept { return a = a + b; }

export constexpr Vector3 &operator-=(Vector3 &a, const Vector3& b) noexcept { return a = a - b; }

export constexpr Vector3& operator*=(Vector3& a, const Vector3& b) noexcept { return a = a * b; }

export constexpr Vector3& operator*=(Vector3& v, const float_t factor) noexcept { return v = v * factor; }

export constexpr Vector3 &operator/=(Vector3 &a, const Vector3& b) noexcept { return a = a / b; }

export constexpr Vector3& operator/=(Vector3& v, const float_t factor) noexcept { return v = v / factor; }

export [[nodiscard]] constexpr bool_t operator==(const Vector3 a, const Vector3 b) noexcept
{
	return a.x == b.x
		&& a.y == b.y
		&& a.z == b.z;
}

export [[nodiscard]] constexpr bool_t operator!=(const Vector3 a, const Vector3 b) noexcept { return !(a == b); }

export template <>
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
