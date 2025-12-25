#pragma once

#include <format>
#include <sstream>
#include <ostream>

#include "Mountain/Math/Vector2.hpp"
#include "Mountain/Math/Vector3.hpp"

/// @file vector4.hpp
/// @brief Defines the Vector4 struct.

/// @brief Declare ImGui Vector4 conversions
/// @note This file needs to be included before ImGui for this macro to work.
#define IM_VEC4_CLASS_EXTRA \
    constexpr ImVec4(const Vector4& f) : x(f.x), y(f.y), z(f.z), w(f.w) {} \
    operator Vector4() const { return Vector4(x, y, z, w); }

struct Matrix;

/// @brief The Vector4 struct represents either a four-dimensional vector or a point.
struct MOUNTAIN_API Vector4
{
    /// @brief The @c x component of this Vector4.
    f32 x = 0.f;
    /// @brief The @c y component of this Vector4.
    f32 y = 0.f;
    /// @brief The @c z component of this Vector4.
    f32 z = 0.f;
    /// @brief The @c w component of this Vector4.
    f32 w = 0.f;

    /// @brief Equivalent to calling the default constructor.
    ATTRIBUTE_NODISCARD
    static constexpr Vector4 Zero() noexcept;

    /// @brief Equivalent to calling the default constructor.
    static constexpr void Zero(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 1, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 0.
    ATTRIBUTE_NODISCARD
    static constexpr Vector4 UnitX() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 1, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 0.
    static constexpr void UnitX(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 1, @c z @c = @c 0, @c w @c = @c 0.
    ATTRIBUTE_NODISCARD
    static constexpr Vector4 UnitY() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 1, @c z @c = @c 0, @c w @c = @c 0.
    static constexpr void UnitY(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 1, @c w @c = @c 0.
    ATTRIBUTE_NODISCARD
    static constexpr Vector4 UnitZ() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 1, @c w @c = @c 0.
    static constexpr void UnitZ(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 1.
    ATTRIBUTE_NODISCARD
    static constexpr Vector4 UnitW() noexcept;

    /// @brief Returns a Vector4 with @c x @c = @c 0, @c y @c = @c 0, @c z @c = @c 0, @c w @c = @c 1.
    static constexpr void UnitW(Vector4* result) noexcept;

    /// @brief Returns a Vector4 with all of its components set to @c 1.
    ATTRIBUTE_NODISCARD
    static constexpr Vector4 One() noexcept;

    /// @brief Returns a Vector4 with all of its components set to @c 1.
    static constexpr void One(Vector4* result) noexcept;

    /// @brief Constructs a Vector4 with everything set to @c 0.
    constexpr Vector4() = default;

    /// @brief Constructs a Vector4 with all its components set to @p xyzw.
    constexpr explicit Vector4(f32 xyzw) noexcept;

    /// @brief Constructs a Vector2 with its components set to the data pointed by @p data.
    ///
    /// This constructor assumes that @p data is a valid pointer pointing to at least 2 @c f32 values.
    ///
    /// @param data The data where the values for this vector's components are located.
    constexpr explicit Vector4(const f32* data) noexcept;

    /// @brief Constructs a Vector3 with set component values.
    ///
    /// @param x The value to set this vector's x components to.
    /// @param y The value to set this vector's y components to.
    /// @param z The value to set this vector's z components to.
    /// @param w The value to set this vector's w components to.
    constexpr Vector4(f32 x, f32 y, f32 z, f32 w) noexcept;

    /// @brief Gets a pointer to the first component of this vector.
    ///
    /// @returns A pointer to the first component of this vector.
    ATTRIBUTE_NODISCARD
    constexpr const f32* Data() const noexcept;

    /// @brief Gets a pointer to the first component of this vector.
    ///
    /// @returns A pointer to the first component of this vector.
    ATTRIBUTE_NODISCARD
    constexpr f32* Data() noexcept;

    /// @brief Returns the length of the vector.
    ATTRIBUTE_NODISCARD
    f32 Length() const noexcept;

    /// @brief Creates a rescaled version of this Vector4.
    ///
    /// @param newLength The new length to give to the Vector4.
    ///
    /// @see Length
    ATTRIBUTE_NODISCARD
    Vector4 Rescaled(f32 newLength) const noexcept;

    /// @brief Returns the squared length of the vector.
    ATTRIBUTE_NODISCARD
    constexpr f32 SquaredLength() const noexcept;

    /// @brief Returns a normalized vector.
    ///
    /// @returns A vector with the same direction but a length of one.
    ATTRIBUTE_NODISCARD
    Vector4 Normalized() const noexcept;

    /// @brief Returns a normalized vector.
    ///
    /// @param result A vector to store the result which is one with the same direction but a length of one.
    void Normalized(Vector4* result) const noexcept;

    /// @brief Check whether all of this vector's components are infinite.
    ATTRIBUTE_NODISCARD
    bool IsInfinity() const noexcept;

    /// @brief Check whether all of this vector's components are NaN.
    ATTRIBUTE_NODISCARD
    bool IsNaN() const noexcept;

    /// @brief Returns a · b.
    ATTRIBUTE_NODISCARD
    static constexpr f32 Dot(const Vector4& a, const Vector4& b) noexcept;

    /// @brief Retrieves this vector's component at index i.
    ///
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    ///
    /// @returns The value of the component at index i.
    ATTRIBUTE_NODISCARD
    constexpr f32 operator[](size_t i) const;

    /// @brief Retrieves this vector's component at index i.
    ///
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    ///
    /// @returns The value of the component at index i.
    ATTRIBUTE_NODISCARD
    constexpr f32& operator[](size_t i);

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

constexpr Vector4::Vector4(const f32 xyzw) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

constexpr Vector4::Vector4(const f32* const data) noexcept : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}

constexpr Vector4::Vector4(const f32 x, const f32 y, const f32 z, const f32 w) noexcept : x(x), y(y), z(z), w(w) {}

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

constexpr const f32* Vector4::Data() const noexcept { return &x; }

constexpr f32* Vector4::Data() noexcept { return &x; }

constexpr f32 Vector4::SquaredLength() const noexcept { return SQ(x) + SQ(y) + SQ(z) + SQ(w); }

constexpr f32 Vector4::Dot(const Vector4& a, const Vector4& b) noexcept {	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

constexpr f32 Vector4::operator[](const size_t i) const
{
    if (i < 4) ATTRIBUTE_LIKELY
        return *(Data() + i);
    ATTRIBUTE_UNLIKELY
        throw std::out_of_range("Vector4 subscript out of range");
}

constexpr f32& Vector4::operator[](const size_t i)
{
    if (i < 4) ATTRIBUTE_LIKELY
        return *(Data() + i);
    ATTRIBUTE_UNLIKELY
        throw std::out_of_range("Vector4 subscript out of range");
}

/// @brief Adds two Vector4 together.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator+(const Vector4& a, const Vector4& b) noexcept { return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

/// @brief Returns the opposite of a Vector4.
///
/// This effectively means replacing all values of this Vector4 with their opposite.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator-(const Vector4& a) noexcept { return Vector4(-a.x, -a.y, -a.z, -a.w); }

/// @brief Subtracts a Vector4 from another one.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator-(const Vector4& a, const Vector4& b) noexcept { return a + -b; }

/// @brief Multiplies two Vector4 component-wise.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator*(const Vector4& a, const Vector4& b) noexcept { return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }

/// @brief Multiplies a Vector4 by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator*(const Vector4& v, const f32 factor) noexcept { return Vector4(v.x * factor, v.y * factor, v.z * factor, v.w * factor); }

/// @brief Multiplies a Vector4 by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator*(const f32 factor, const Vector4 v) noexcept { return v * factor; }

/// @brief Divides a Vector4 by another one.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator/(const Vector4& a, const Vector4& b) noexcept { return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }

/// @brief Divides a Vector4 by a @p factor.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator/(const Vector4& v, const f32 factor) noexcept { const f32 invFactor = 1.f / factor; return Vector4(v.x * invFactor, v.y * invFactor, v.z * invFactor, v.w * invFactor); }

/// @brief Adds two Vector4 according to @ref operator+(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4& operator+=(Vector4& a, const Vector4& b) noexcept { return a = a + b; }

/// @brief Subtracts a Vector4 from another one according to @ref operator-(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4 &operator-=(Vector4 &a, const Vector4& b) noexcept { return a = a - b; }

/// @brief Multiplies two Vector4 component-wise according to @ref operator*(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4& operator*=(Vector4& a, const Vector4& b) noexcept { return a = a * b; }

/// @brief Multiplies a Vector4 by a @p factor according to @ref operator*(const Vector4&, const f32), placing the result in @p v.
constexpr Vector4& operator*=(Vector4& v, const f32 factor) noexcept { return v = v * factor; }

/// @brief Divides two Vector4 component-wise according to @ref operator/(const Vector4&, const Vector4&), placing the result in @p a.
constexpr Vector4 &operator/=(Vector4 &a, const Vector4& b) noexcept { return a = a / b; }

/// @brief Divides a Vector4 by a @p factor according to @ref operator/(const Vector4&, const f32), placing the result in @p v.
constexpr Vector4& operator/=(Vector4& v, const f32 factor) noexcept { return v = v / factor; }

/// @brief Checks if two Vector4 are equal.
ATTRIBUTE_NODISCARD
constexpr bool operator==(const Vector4 a, const Vector4 b) noexcept
{
    return a.x == b.x
        && a.y == b.y
        && a.z == b.z
        && a.w == b.w;
}

/// @brief Checks if two Vector4 are different.
ATTRIBUTE_NODISCARD
constexpr bool operator!=(const Vector4 a, const Vector4 b) noexcept { return !(a == b); }

/// @brief Streams a Vector4 into @p out, printing its values one by one on a single line.
MOUNTAIN_API std::ostream& operator<<(std::ostream& out, const Vector4& v) noexcept;

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
constexpr typename ParseContext::iterator std::formatter<Vector4, c8>::parse(ParseContext& ctx)
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
