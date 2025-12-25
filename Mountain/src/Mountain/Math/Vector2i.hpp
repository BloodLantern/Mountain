#pragma once

#include <format>
#include <sstream>
#include <ostream>

#include "Mountain/Math/Vector2.hpp"

/// @file vector2i.hpp
/// @brief Defines the Vector2i struct.

struct Vector3;
struct Vector4;

/// @brief The Vector2i struct represents either a two-dimensional vector or a point.
struct MOUNTAIN_API Vector2i
{
    /// @brief The @c x component of this Vector2i.
    s32 x = 0;

    /// @brief The @c y component of this Vector2i.
    s32 y = 0;

    /// @brief Equivalent to calling the default constructor.
    ATTRIBUTE_NODISCARD
    static constexpr Vector2i Zero() noexcept;

    /// @brief Returns a Vector2i with @c x @c = @c 1, @c y @c = @c 0.
    ATTRIBUTE_NODISCARD
    static constexpr Vector2i UnitX() noexcept;

    /// @brief Returns a Vector2i with @c x @c = @c 0, @c y @c = @c 1.
    ATTRIBUTE_NODISCARD
    static constexpr Vector2i UnitY() noexcept;

    /// @brief Returns a Vector2i with both its components set to @c 1.
    ATTRIBUTE_NODISCARD
    static constexpr Vector2i One() noexcept;

    /// @brief Returns a · b.
    ATTRIBUTE_NODISCARD
    static constexpr f32 Dot(Vector2i a, Vector2i b) noexcept;

    /// @brief Returns a x b.
    ///
    /// For a Vector2i this is only the determinant.
    ATTRIBUTE_NODISCARD
    static constexpr f32 Cross(Vector2i a, Vector2i b) noexcept;

    /// @brief Returns the determinant of 'a' and 'b'.
    ATTRIBUTE_NODISCARD
    static constexpr f32 Determinant(Vector2i a, Vector2i b) noexcept;

    constexpr Vector2i() = default;

    /// @brief Constructs a Vector2i with both its components set to 'xy'.
    constexpr explicit Vector2i(s32 xy);

    /// @brief Constructs a Vector2i with its components set to the data pos32ed by @c data.
    ///
    /// This constructor assumes that @c data is a valid pointer pointing to at least 2 @c s32 values.
    ///
    /// @param data The data where the values for this vector's components are located.
    constexpr explicit Vector2i(const s32* data) noexcept;

    /// @brief Constructs a Vector2i with set component values.
    ///
    /// @param x The value to set this vector's x component to.
    /// @param y The value to set this vector's y component to.
    constexpr Vector2i(s32 x, s32 y);

    /// @brief 	Gets a pointer to the first component of this vector.
    /// @returns A pointer to the first component of this vector.
    ATTRIBUTE_NODISCARD
    constexpr const s32* Data() const noexcept;

    /// @brief 	Gets a pointer to the first component of this vector.
    ///
    /// @returns A pointer to the first component of this vector.
    ATTRIBUTE_NODISCARD
    constexpr s32* Data() noexcept;

    /// @brief Returns the length of the vector.
    ATTRIBUTE_NODISCARD
    f32 Length() const noexcept;

    /// @brief Returns the squared length of the vector.
    ATTRIBUTE_NODISCARD
    constexpr f32 SquaredLength() const noexcept;

    /// @brief Returns a normalized vector.
    ///
    /// @returns A vector with the same direction but a length of one.
    ATTRIBUTE_NODISCARD
    Vector2 Normalized() const;

    /// @brief Returns the normal vector to this one.
    ///
    /// @returns A vector with the same length but a normal direction.
    ATTRIBUTE_NODISCARD
    Vector2 Normal() const;

    /// @brief 	Retrieves this vector's component at index i.
    ///
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    ///
    /// @returns The value of the component at index i.
    ATTRIBUTE_NODISCARD
    constexpr s32 operator[](size_t i) const;

    /// @brief 	Retrieves this vector's component at index i.
    ///
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    ///
    /// @returns The value of the component at index i.
    ATTRIBUTE_NODISCARD
    constexpr s32& operator[](size_t i);

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

constexpr Vector2i::Vector2i(const s32 xy): x(xy), y(xy) {}

constexpr Vector2i::Vector2i(const s32* const data) noexcept : x(data[0]), y(data[1]) {}

constexpr Vector2i::Vector2i(const s32 x, const s32 y): x(x), y(y) {}

constexpr Vector2i Vector2i::Zero() noexcept { return Vector2i(); }

constexpr Vector2i Vector2i::UnitX() noexcept { return Vector2i(1, 0); }

constexpr Vector2i Vector2i::UnitY() noexcept { return Vector2i(0, 1); }

constexpr Vector2i Vector2i::One() noexcept { return Vector2i(1); }

constexpr f32 Vector2i::Dot(const Vector2i a, const Vector2i b) noexcept { return static_cast<f32>(a.x * b.x + a.y * b.y); }

constexpr f32 Vector2i::Cross(const Vector2i a, const Vector2i b) noexcept { return Determinant(a, b); }

constexpr f32 Vector2i::Determinant(const Vector2i a, const Vector2i b) noexcept { return static_cast<f32>(a.x * b.y - b.x * a.y); }

constexpr const s32* Vector2i::Data() const noexcept { return &x; }

constexpr s32* Vector2i::Data() noexcept { return &x; }

constexpr f32 Vector2i::SquaredLength() const noexcept { return static_cast<f32>(x * x + y * y); }

constexpr s32 Vector2i::operator[](const size_t i) const
{
    if (i < 2) ATTRIBUTE_LIKELY
        return *(Data() + i);
    ATTRIBUTE_UNLIKELY
        throw std::out_of_range("Vector2i subscript out of range");
}

constexpr s32& Vector2i::operator[](const size_t i)
{
    if (i < 2) ATTRIBUTE_LIKELY
        return *(Data() + i);
    ATTRIBUTE_UNLIKELY
        throw std::out_of_range("Vector2i subscript out of range");
}

/// @brief Adds two Vector2i together.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator+(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x + b.x, a.y + b.y); }

/// @brief Returns the opposite of a Vector2i.
///
/// This effectively means replacing all values of this Vector2i with their opposite.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator-(const Vector2i a) noexcept { return Vector2i(-a.x, -a.y); }

/// @brief Subtracts a Vector2i from another one.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator-(const Vector2i a, const Vector2i b) noexcept { return a + -b; }

/// @brief Multiplies two Vector2i component-wise.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator*(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x * b.x, a.y * b.y); }

/// @brief Multiplies a Vector2i by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator*(const Vector2i v, const s32 factor) noexcept { return Vector2i(v.x * factor, v.y * factor); }

/// @brief Multiplies a Vector2i by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator*(const s32 factor, const Vector2i v) noexcept { return v * factor; }

/// @brief Multiplies a Vector2i by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector2 operator*(const Vector2i v, const f32 factor) noexcept
{
    return Vector2(static_cast<f32>(v.x) * factor, static_cast<f32>(v.y) * factor);
}

/// @brief Multiplies a Vector2i by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector2 operator*(const f32 factor, const Vector2i v) noexcept { return v * factor; }

/// @brief Divides a Vector2i by another one.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator/(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x / b.x, a.y / b.y); }

/// @brief Divides a Vector2i by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector2i operator/(const Vector2i v, const s32 factor) noexcept { return Vector2i(v.x / factor, v.y / factor); }

/// @brief Divides a Vector2i by another one.
ATTRIBUTE_NODISCARD
constexpr Vector2 operator/(const Vector2i a, const Vector2 b) noexcept { return Vector2(static_cast<f32>(a.x) / static_cast<f32>(b.x), static_cast<f32>(a.y) / static_cast<f32>(b.y)); }

/// @brief Divides a Vector2i by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector2 operator/(const Vector2i v, const f32 factor) noexcept { return Vector2(static_cast<f32>(v.x) / factor, static_cast<f32>(v.y) / factor); }

/// @brief Adds two Vector2i according to @ref operator+(const Vector2i, const Vector2i), placing the result in @p a.
constexpr Vector2i& operator+=(Vector2i& a, const Vector2i b) noexcept { return a = a + b; }

/// @brief Subtracts a Vector2i from another one according to @ref operator-(const Vector2i, const Vector2i), placing the result in @p a.
constexpr Vector2i &operator-=(Vector2i &a, const Vector2i b) noexcept { return a = a - b; }

/// @brief Multiplies two Vector2i component-wise according to @ref operator*(const Vector2i, const Vector2i), placing the result in @p a.
constexpr Vector2i& operator*=(Vector2i& a, const Vector2i b) noexcept { return a = a * b; }

/// @brief Multiplies a Vector2i by a @p factor according to @ref operator*(const Vector2i, const s32), placing the result in @p v.
constexpr Vector2i& operator*=(Vector2i& v, const s32 factor) noexcept { return v = v * factor; }

/// @brief Divides a Vector2i by a @p factor according to @ref operator/(const Vector2i, const s32), placing the result in @p v.
constexpr Vector2i& operator/=(Vector2i& v, const s32 factor) noexcept { return v = v / factor; }

/// @brief Checks if two Vector2i are considered equal using @c Calc::Equals.
ATTRIBUTE_NODISCARD
constexpr bool operator==(const Vector2i a, const Vector2i b) noexcept { return a.x == b.x && a.y == b.y; }

/// @brief Checks if two Vector2i are considered different using @c Calc::Equals.
ATTRIBUTE_NODISCARD
constexpr bool operator!=(const Vector2i a, const Vector2i b) noexcept { return !(a == b); }

/// @brief Streams a Vector2i into @p out, printing its values one by one on a single line.
MOUNTAIN_API std::ostream& operator<<(std::ostream& out, Vector2i v) noexcept;

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
constexpr typename ParseContext::iterator std::formatter<Vector2i, c8>::parse(ParseContext& ctx)
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
