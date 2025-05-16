#pragma once

#include <format>
#include <sstream>

#include <ostream>

#include "Maths/vector2.hpp"

/// @file vector2i.hpp
/// @brief Defines the Vector2i class.

class Vector3;
class Vector4;

/// @brief The Vector2i class represents either a two-dimensional vector or a point.
class MATH_TOOLBOX Vector2i
{
public:
    /// @brief The @c x component of this Vector2i.
    int32_t x = 0;
    
    /// @brief The @c y component of this Vector2i.
    int32_t y = 0;

    /// @brief Equivalent to calling the default constructor.
    [[nodiscard]]
    static constexpr Vector2i Zero() noexcept;

    /// @brief Returns a Vector2i with @c x @c = @c 1, @c y @c = @c 0.
    [[nodiscard]]
    static constexpr Vector2i UnitX() noexcept;

    /// @brief Returns a Vector2i with @c x @c = @c 0, @c y @c = @c 1.
    [[nodiscard]]
    static constexpr Vector2i UnitY() noexcept;

    /// @brief Returns a Vector2i with both its components set to @c 1.
    [[nodiscard]]
    static constexpr Vector2i One() noexcept;
    
    /// @brief Returns a · b.
    [[nodiscard]]
    static constexpr float_t Dot(Vector2i a, Vector2i b) noexcept;
    
    /// @brief Returns a x b.
    /// 
    /// For a Vector2i this is only the determinant.
    [[nodiscard]]
    static constexpr float_t Cross(Vector2i a, Vector2i b) noexcept;
    
    /// @brief Returns the determinant of 'a' and 'b'.
    [[nodiscard]]
    static constexpr float_t Determinant(Vector2i a, Vector2i b) noexcept;

    constexpr Vector2i() = default;

    /// @brief Constructs a Vector2i with both its components set to 'xy'.
    constexpr explicit Vector2i(int32_t xy);
    
    /// @brief Constructs a Vector2i with its components set to the data point32_ted by @c data.
    /// 
    /// This constructor assumes that @c data is a valid pointer pointing to at least 2 @c int32_t values.
    /// 
    /// @param data The data where the values for this vector's components are located.
    constexpr explicit Vector2i(const int32_t* data) noexcept;

    /// @brief Constructs a Vector2i with set component values.
    /// 
    /// @param x The value to set this vector's x component to.
    /// @param y The value to set this vector's y component to.
    constexpr Vector2i(int32_t x, int32_t y);

    /// @brief 	Gets a pointer to the first component of this vector.
    /// @returns A pointer to the first component of this vector.
    [[nodiscard]]
    constexpr const int32_t* Data() const noexcept;

    /// @brief 	Gets a pointer to the first component of this vector.
    /// 
    /// @returns A pointer to the first component of this vector.
    [[nodiscard]]
    constexpr int32_t* Data() noexcept;

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
    Vector2 Normalized() const;
    
    /// @brief Returns the normal vector to this one.
    /// 
    /// @returns A vector with the same length but a normal direction.
    [[nodiscard]]
    Vector2 Normal() const;

    /// @brief 	Retrieves this vector's component at index i.
    /// 
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    /// 
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr int32_t operator[](size_t i) const;
    
    /// @brief 	Retrieves this vector's component at index i.
    /// 
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    /// 
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr int32_t& operator[](size_t i);

    /// @brief Converts this Vector2i to a Vector2.
    operator Vector2() const;

    /// @brief Converts this Vector2i to a Vector3 by giving it a @c z value of @c 0.
    explicit operator Vector3() const;

    /// @brief Converts this Vector2i to a Vector4 by giving it a @c z value of @c 0 and a @c w value of @c 1.
    explicit operator Vector4() const;
};

static_assert(std::is_default_constructible_v<Vector2i>, "Class Vector2i must be default constructible.");
static_assert(std::is_copy_constructible_v<Vector2i>, "Class Vector2i must be copy constructible.");
static_assert(std::is_move_constructible_v<Vector2i>, "Class Vector2i must be move constructible.");
static_assert(std::is_copy_assignable_v<Vector2i>, "Class Vector2i must be copy assignable.");
static_assert(std::is_move_assignable_v<Vector2i>, "Class Vector2i must be move assignable.");

constexpr Vector2i::Vector2i(const int32_t xy): x(xy), y(xy) {}

constexpr Vector2i::Vector2i(const int32_t* const data) noexcept : x(data[0]), y(data[1]) {}

constexpr Vector2i::Vector2i(const int32_t x, const int32_t y): x(x), y(y) {}

constexpr Vector2i Vector2i::Zero() noexcept { return Vector2i(); }

constexpr Vector2i Vector2i::UnitX() noexcept { return Vector2i(1, 0); }

constexpr Vector2i Vector2i::UnitY() noexcept { return Vector2i(0, 1); }

constexpr Vector2i Vector2i::One() noexcept { return Vector2i(1); }

constexpr float_t Vector2i::Dot(const Vector2i a, const Vector2i b) noexcept { return static_cast<float_t>(a.x * b.x + a.y * b.y); }

constexpr float_t Vector2i::Cross(const Vector2i a, const Vector2i b) noexcept { return Determinant(a, b); }

constexpr float_t Vector2i::Determinant(const Vector2i a, const Vector2i b) noexcept { return static_cast<float_t>(a.x * b.y - b.x * a.y); }

constexpr const int32_t* Vector2i::Data() const noexcept { return &x; }

constexpr int32_t* Vector2i::Data() noexcept { return &x; }

constexpr float_t Vector2i::SquaredLength() const noexcept { return static_cast<float_t>(x * x + y * y); }

constexpr int32_t Vector2i::operator[](const size_t i) const
{
    if (i < 2) [[likely]]
        return *(Data() + i);
    [[unlikely]]
        throw std::out_of_range("Vector2i subscript out of range");
}

constexpr int32_t& Vector2i::operator[](const size_t i)
{
    if (i < 2) [[likely]]
        return *(Data() + i);
    [[unlikely]]
        throw std::out_of_range("Vector2i subscript out of range");
}

/// @brief Adds two Vector2i together.
[[nodiscard]]
constexpr Vector2i operator+(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x + b.x, a.y + b.y); }

/// @brief Returns the opposite of a Vector2i.
///
/// This effectively means replacing all values of this Vector2i with their opposite.
[[nodiscard]]
constexpr Vector2i operator-(const Vector2i a) noexcept { return Vector2i(-a.x, -a.y); }

/// @brief Subtracts a Vector2i from another one.
[[nodiscard]]
constexpr Vector2i operator-(const Vector2i a, const Vector2i b) noexcept { return a + -b; }

/// @brief Multiplies two Vector2i component-wise.
[[nodiscard]]
constexpr Vector2i operator*(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x * b.x, a.y * b.y); }

/// @brief Multiplies a Vector2i by a @p factor.
[[nodiscard]]
constexpr Vector2i operator*(const Vector2i v, const int32_t factor) noexcept { return Vector2i(v.x * factor, v.y * factor); }

/// @brief Multiplies a Vector2i by a @p factor.
[[nodiscard]]
constexpr Vector2i operator*(const int32_t factor, const Vector2i v) noexcept { return v * factor; }

/// @brief Multiplies a Vector2i by a @p factor.
[[nodiscard]]
constexpr Vector2 operator*(const Vector2i v, const float_t factor) noexcept
{
    return Vector2(static_cast<float_t>(v.x) * factor, static_cast<float_t>(v.y) * factor);
}

/// @brief Multiplies a Vector2i by a @p factor.
[[nodiscard]]
constexpr Vector2 operator*(const float_t factor, const Vector2i v) noexcept { return v * factor; }

/// @brief Divides a Vector2i by another one.
[[nodiscard]]
constexpr Vector2i operator/(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x / b.x, a.y / b.y); }

/// @brief Divides a Vector2i by a @p factor.
[[nodiscard]]
constexpr Vector2i operator/(const Vector2i v, const int32_t factor) noexcept { return Vector2i(v.x / factor, v.y / factor); }

/// @brief Divides a Vector2i by another one.
[[nodiscard]]
constexpr Vector2 operator/(const Vector2i a, const Vector2 b) noexcept { return Vector2(static_cast<float_t>(a.x) / static_cast<float_t>(b.x), static_cast<float_t>(a.y) / static_cast<float_t>(b.y)); }

/// @brief Divides a Vector2i by a @p factor.
[[nodiscard]]
constexpr Vector2 operator/(const Vector2i v, const float_t factor) noexcept { return Vector2(static_cast<float_t>(v.x) / factor, static_cast<float_t>(v.y) / factor); }

/// @brief Adds two Vector2i according to @ref operator+(const Vector2i, const Vector2i), placing the result in @p a.
constexpr Vector2i& operator+=(Vector2i& a, const Vector2i b) noexcept { return a = a + b; }

/// @brief Subtracts a Vector2i from another one according to @ref operator-(const Vector2i, const Vector2i), placing the result in @p a.
constexpr Vector2i &operator-=(Vector2i &a, const Vector2i b) noexcept { return a = a - b; }

/// @brief Multiplies two Vector2i component-wise according to @ref operator*(const Vector2i, const Vector2i), placing the result in @p a.
constexpr Vector2i& operator*=(Vector2i& a, const Vector2i b) noexcept { return a = a * b; }

/// @brief Multiplies a Vector2i by a @p factor according to @ref operator*(const Vector2i, const int32_t), placing the result in @p v.
constexpr Vector2i& operator*=(Vector2i& v, const int32_t factor) noexcept { return v = v * factor; }

/// @brief Checks if two Vector2i are considered equal using @c Calc::Equals.
[[nodiscard]]
constexpr bool_t operator==(const Vector2i a, const Vector2i b) noexcept { return a.x == b.x && a.y == b.y; }

/// @brief Checks if two Vector2i are considered different using @c Calc::Equals.
[[nodiscard]]
constexpr bool_t operator!=(const Vector2i a, const Vector2i b) noexcept { return !(a == b); }

/// @brief Streams a Vector2i into @p out, printing its values one by one on a single line.
MATH_TOOLBOX std::ostream& operator<<(std::ostream& out, Vector2i v) noexcept;

template <>
struct std::formatter<Vector2i>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Vector2i v, FmtContext& ctx) const;

private:
    std::string m_Format;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Vector2i, char_t>::parse(ParseContext& ctx)
{
    auto it = ctx.begin();
    if (it == ctx.end())
        return it;

    while (*it != '}' && it != ctx.end())
        m_Format += *it++;

    return it;
}

template <class FmtContext>
typename FmtContext::iterator std::formatter<Vector2i>::format(Vector2i v, FmtContext &ctx) const
{
    std::ostringstream out;

    out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(v.x, v.y));

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
