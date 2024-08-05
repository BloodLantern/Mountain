#pragma once

#include <format>
#include <sstream>

#include <ostream>
#include <stdexcept>

#include "Maths/core.hpp"

/// @file vector2.hpp
/// @brief Defines the Vector2 class.

class Vector2i;
class Vector3;
class Vector4;

/// @brief The Vector2 class represents either a two-dimensional vector or a point.
class MATH_TOOLBOX Vector2
{
public:
    /// @brief The @c x component of this Vector2.
    float_t x = 0.f;
    
    /// @brief The @c y component of this Vector2.
    float_t y = 0.f;

    /// @brief Equivalent to calling the default constructor.
    [[nodiscard]]
    static constexpr Vector2 Zero() noexcept;

    /// @brief Returns a Vector2 with @c x @c = @c 1, @c y @c = @c 0.
    [[nodiscard]]
    static constexpr Vector2 UnitX() noexcept;

    /// @brief Returns a Vector2 with @c x @c = @c 0, @c y @c = @c 1.
    [[nodiscard]]
    static constexpr Vector2 UnitY() noexcept;

    /// @brief Returns a Vector2 with both its components set to @c 1.
    [[nodiscard]]
    static constexpr Vector2 One() noexcept;

    /// @brief Returns a · b.
    [[nodiscard]]
    static constexpr float_t Dot(Vector2 a, Vector2 b) noexcept;

    /// @brief Returns a x b.
    /// 
    /// For a Vector2, this is simply the determinant.
    [[nodiscard]]
    static constexpr float_t Cross(Vector2 a, Vector2 b) noexcept;

    /// @brief Returns the determinant of 'a' and 'b'.
    [[nodiscard]]
    static constexpr float_t Determinant(Vector2 a, Vector2 b) noexcept;

    /// @brief Constructs a Vector2 with both its components set to 0.
    constexpr Vector2() = default;
    
    /// @brief Constructs a Vector2 with both its components set to @p xy.
    /// 
    /// @param xy The value to set this vector's x and y components to.
    constexpr explicit Vector2(float_t xy) noexcept;
    
    /// @brief Constructs a Vector2 with its components set to the data pointed by @p data.
    /// 
    /// This constructor assumes that @p data is a valid pointer pointing to at least 2 @c float_t values.
    /// 
    /// @param data The data where the values for this vector's components are located.
    constexpr explicit Vector2(const float_t* data) noexcept;

    /// @brief Constructs a Vector2 with set component values.
    /// 
    /// @param x The value to set this vector's x component to.
    /// @param y The value to set this vector's y component to.
    constexpr Vector2(float_t x, float_t y) noexcept;

    /// @brief	Gets a pointer to the first component of this vector.
    /// 
    /// @returns A pointer to the first component of this vector.
    [[nodiscard]]
    constexpr const float_t* Raw() const noexcept;

    /// @brief 	Gets a pointer to the first component of this vector.
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
    Vector2 Normalized() const noexcept;

    /// @brief Returns the normal vector to this one.
    /// 
    /// @returns A vector with the same length but a normal direction.
    [[nodiscard]]
    Vector2 Normal() const noexcept;

    /// @brief Returns this vector, rotated by @p angle radians.
    [[nodiscard]]
    Vector2 Rotated(float_t angle) const noexcept;

    /// @brief Returns this vector, rotated using the given cos and sin values.
    [[nodiscard]]
    Vector2 Rotated(float_t c, float_t s) const noexcept;

    /// @brief 	Check whether all of this vector's components are infinite.
    [[nodiscard]]
    bool_t IsInfinity() const noexcept;

    /// @brief 	Check whether all of this vector's components are NaN.
    [[nodiscard]]
    bool_t IsNaN() const noexcept;

    /// @brief 	Retrieves this vector's component at index i.
    /// 
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    /// 
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr float_t operator[](size_t i) const;

    /// @brief 	Retrieves this vector's component at index i.
    /// 
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    /// 
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr float_t& operator[](size_t i);

    /// @brief Converts this Vector2 to a Vector2i by casting its components to @c int32_t.
    explicit operator Vector2i() const noexcept;
    
    /// @brief Converts this Vector2 to a Vector3 by giving it a @c z value of @c 0.
    explicit operator Vector3() const noexcept;

    /// @brief Converts this Vector2 to a Vector4 by giving it a @c z value of @c 0 and a @c w value of @c 1.
    explicit operator Vector4() const noexcept;
};

static_assert(std::is_default_constructible_v<Vector2>, "Class Vector2 must be default constructible.");
static_assert(std::is_copy_constructible_v<Vector2>, "Class Vector2 must be copy constructible.");
static_assert(std::is_move_constructible_v<Vector2>, "Class Vector2 must be move constructible.");
static_assert(std::is_copy_assignable_v<Vector2>, "Class Vector2 must be copy assignable.");
static_assert(std::is_move_assignable_v<Vector2>, "Class Vector2 must be move assignable.");

constexpr Vector2::Vector2(const float_t xy) noexcept : x(xy), y(xy) {}

constexpr Vector2::Vector2(const float_t* const data) noexcept : x(data[0]), y(data[1]) {}

constexpr Vector2::Vector2(const float_t x, const float_t y) noexcept : x(x), y(y) {}

constexpr Vector2 Vector2::Zero() noexcept { return Vector2(); }

constexpr Vector2 Vector2::UnitX() noexcept { return Vector2(1.f, 0.f); }

constexpr Vector2 Vector2::UnitY() noexcept { return Vector2(0.f, 1.f); }

constexpr Vector2 Vector2::One() noexcept { return Vector2(1); }

constexpr float_t Vector2::Dot(const Vector2 a, const Vector2 b) noexcept { return a.x * b.x + a.y * b.y; }

constexpr float_t Vector2::Cross(const Vector2 a, const Vector2 b) noexcept { return Determinant(a, b); }

constexpr float_t Vector2::Determinant(const Vector2 a, const Vector2 b) noexcept { return a.x * b.y - b.x * a.y; }

constexpr const float_t* Vector2::Raw() const noexcept { return& x; }

constexpr float_t* Vector2::Raw() noexcept { return& x; }

constexpr float_t Vector2::SquaredLength() const noexcept { return SQ(x) + SQ(y); }

constexpr float_t Vector2::operator[](const size_t i) const
{
    if (i < 2) [[likely]]
        return *(Raw() + i);
    [[unlikely]]
    throw std::out_of_range("Vector2 subscript out of range");
}

constexpr float_t& Vector2::operator[](const size_t i)
{
    if (i < 2) [[likely]]
        return *(Raw() + i);
    [[unlikely]]
    throw std::out_of_range("Vector2 subscript out of range");
}

/// @brief Adds two Vector2 together.
[[nodiscard]]
constexpr Vector2 operator+(const Vector2 a, const Vector2 b) noexcept { return Vector2(a.x + b.x, a.y + b.y); }

/// @brief Returns the opposite of a Vector2.
///
/// This effectively means replacing all values of this Vector2 with their opposite.
[[nodiscard]]
constexpr Vector2 operator-(const Vector2 a) noexcept { return Vector2(-a.x, -a.y); }

/// @brief Subtracts a Vector2 from another one.
[[nodiscard]]
constexpr Vector2 operator-(const Vector2 a, const Vector2 b) noexcept { return a + -b; }

/// @brief Multiplies two Vector2 component-wise.
[[nodiscard]]
constexpr Vector2 operator*(const Vector2 a, const Vector2 b) noexcept { return Vector2(a.x * b.x, a.y * b.y); }

/// @brief Multiplies a Vector2 by a @p factor.
[[nodiscard]]
constexpr Vector2 operator*(const Vector2 v, const float_t factor) noexcept { return Vector2(v.x * factor, v.y * factor); }

/// @brief Multiplies a Vector2 by a @p factor.
[[nodiscard]]
constexpr Vector2 operator*(const float_t factor, const Vector2 v) noexcept { return v * factor; }

/// @brief Divides a Vector2 by another one.
[[nodiscard]]
constexpr Vector2 operator/(const Vector2 a, const Vector2 b) noexcept { return Vector2(a.x / b.x, a.y / b.y); }

/// @brief Divides a Vector2 by a @p factor.
[[nodiscard]]
constexpr Vector2 operator/(const Vector2 v, const float_t factor) noexcept { const float_t invFactor = 1.f / factor; return Vector2(v.x * invFactor, v.y * invFactor); }

/// @brief Adds two Vector2 according to @ref operator+(const Vector2, const Vector2), placing the result in @p a.
constexpr Vector2& operator+=(Vector2& a, const Vector2 b) noexcept { return a = a + b; }

/// @brief Subtracts a Vector2 from another one according to @ref operator-(const Vector2, const Vector2), placing the result in @p a.
constexpr Vector2& operator-=(Vector2& a, const Vector2 b) noexcept { return a = a - b; }

/// @brief Multiplies two Vector2 component-wise according to @ref operator*(const Vector2, const Vector2), placing the result in @p a.
constexpr Vector2& operator*=(Vector2& a, const Vector2 b) noexcept { return a = a * b; }

/// @brief Multiplies a Vector2 by a @p factor according to @ref operator*(const Vector2, const float_t), placing the result in @p v.
constexpr Vector2& operator*=(Vector2& v, const float_t factor) noexcept { return v = v * factor; }

/// @brief Divides two Vector2 component-wise according to @ref operator/(const Vector2, const Vector2), placing the result in @p a.
constexpr Vector2& operator/=(Vector2& a, const Vector2 b) noexcept { return a = a / b; }

/// @brief Divides a Vector2 by a @p factor according to @ref operator/(const Vector2, const float_t), placing the result in @p v.
constexpr Vector2& operator/=(Vector2& v, const float_t factor) noexcept { return v = v / factor; }

/// @brief Checks if two Vector2 are equal.
[[nodiscard]]
constexpr bool_t operator==(const Vector2 a, const Vector2 b) noexcept
{
    return a.x == b.x
        && a.y == b.y;
}

/// @brief Checks if two Vector2 are different.
[[nodiscard]]
constexpr bool_t operator!=(const Vector2 a, const Vector2 b) noexcept { return !(a == b); }

/// @brief Streams a Vector2 into @p out, printing its values one by one on a single line.
MATH_TOOLBOX std::ostream& operator<<(std::ostream& out, Vector2 v) noexcept;

template <>
struct std::formatter<Vector2>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Vector2 v, FmtContext& ctx) const;
    
private:
    std::string m_Format;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Vector2, char_t>::parse(ParseContext& ctx)
{
    auto it = ctx.begin();
    if (it == ctx.end())
        return it;

    while (*it != '}' && it != ctx.end())
        m_Format += *it++;
    
    return it;
}

template <class FmtContext>
typename FmtContext::iterator std::formatter<Vector2>::format(Vector2 v, FmtContext& ctx) const
{
    std::ostringstream out;

    out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(v.x, v.y));

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
