#pragma once

#include <format>
#include <sstream>

#include <ostream>

#include "Maths/calc.hpp"
#include "Maths/vector3.hpp"
#include "Maths/vector4.hpp"

/// @file quaternion.hpp
/// @brief Defines the Quaternion class.

/// @brief The Quaternion class represents a 4-dimensional vector mainly used for mathematical calculations revolving around rotations.
class MATH_TOOLBOX Quaternion
{
public:
    /// @brief The imaginary part of this Quaternion. Represents the @c x, @c y, and @c z components.
    Vector3 imaginary;
    
    /// @brief The real part of this Quaternion. Represents the @c w component.
    float_t real = 0.f;

    /// @brief Equivalent to calling the default constructor.
    /// 
    /// @returns A Quaternion with everything set to 0.
    /// @see Quaternion()
    [[nodiscard]]
    static constexpr Quaternion Zero() noexcept;

    /// @brief Equivalent to calling the default constructor.
    /// 
    /// @param result The output value.
    /// @see Zero()
    static constexpr void Zero(Quaternion* result) noexcept;

    /// @brief Create a constant Quaternion of value @c { x = 1, y = 0, z = 0, w = 0 }.
    /// 
    /// @returns A Quaternion with and @c x value of @c 1, and everything else set to 0.
    [[nodiscard]]
    static constexpr Quaternion UnitX() noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 1, y = 0, z = 0, w = 0 }.
    /// 
    /// @param result The output value.
    /// @see UnitX()
    static constexpr void UnitX(Quaternion* result) noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 0, y = 1, z = 0, w = 0 }.
    /// 
    /// @returns A Quaternion with and @c y value of @c 1, and everything else set to 0.
    [[nodiscard]]
    static constexpr Quaternion UnitY() noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 0, y = 1, z = 0, w = 0 }.
    /// 
    /// @param result The output value.
    /// @see UnitY()
    static constexpr void UnitY(Quaternion* result) noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 0, y = 0, z = 1, w = 0 }.
    /// 
    /// @returns A Quaternion with and @c z value of @c 1, and everything else set to 0.
    [[nodiscard]]
    static constexpr Quaternion UnitZ() noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 0, y = 0, z = 1, w = 0 }.
    /// 
    /// @param result The output value.
    /// @see UnitZ()
    static constexpr void UnitZ(Quaternion* result) noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 0, y = 0, z = 0, w = 1 }.
    /// 
    /// @returns A Quaternion with and @c w value of @c 1, and everything else set to 0.
    [[nodiscard]]
    static constexpr Quaternion UnitW() noexcept;
    
    /// @brief Create a constant Quaternion of value @c { x = 0, y = 0, z = 0, w = 1 }.
    /// 
    /// @param result The output value.
    /// @see UnitW()
    static constexpr void UnitW(Quaternion* result) noexcept;

    /// @brief Equivalent to calling @ref UnitW().
    /// 
    /// @returns A Quaternion with and @c w value of @c 1, and everything else set to @c 0.
    [[nodiscard]]
    static constexpr Quaternion Identity() noexcept;

    /// @brief Equivalent to calling @ref Quaternion::UnitW().
    /// 
    /// @param result The output value.
    /// @see UnitW(Quaternion*)
    static constexpr void Identity(Quaternion* result) noexcept;

    /// @brief Create a rotation Quaternion from an axis-angle rotation.
    /// 
    /// @param axis The axis around which the rotation occurs.
    /// @param angle The rotation angle.
    /// @returns A rotation Quaternion equivalent to the given axis-angle rotation.
    [[nodiscard]]
    static Quaternion FromAxisAngle(const Vector3& axis, float_t angle) noexcept;

    /// @brief Create a rotation Quaternion from an axis-angle rotation.
    /// 
    /// @param axis The axis around which the rotation occurs.
    /// @param angle The rotation angle.
    /// @param result The output value.
    /// @see FromAxisAngle(const Vector3&, float_t)
    static void FromAxisAngle(const Vector3& axis, float_t angle, Quaternion* result) noexcept;
    
    /// @brief Create a rotation Quaternion from an axis-angle rotation.
    /// 
    /// @param rotation The euler rotation vector.
    /// @returns A rotation Quaternion equivalent to the given axis-angle rotation.
    [[nodiscard]]
    static Quaternion FromEuler(const Vector3& rotation) noexcept;
    
    /// @brief Create a rotation Quaternion from an axis-angle rotation.
    /// 
    /// @param rotation The euler rotation vector.
    /// @param result The output value.
    /// @see FromEuler(const Vector3&)
    static void FromEuler(const Vector3& rotation, Quaternion* result) noexcept;
    
    /// @brief Create a rotation Quaternion from an axis-angle rotation.
    /// 
    /// @param rotation The rotation Matrix.
    /// @returns A rotation Quaternion equivalent to the given axis-angle rotation.
    [[nodiscard]]
    static Quaternion FromRotationMatrix(const Matrix& rotation) noexcept;
    
    /// @brief Create a rotation Quaternion from an axis-angle rotation.
    /// 
    /// @param rotation The rotation Matrix.
    /// @param result The output value.
    /// @see FromRotationMatrix(const Matrix&)
    static void FromRotationMatrix(const Matrix& rotation, Quaternion* result) noexcept;
    
    /// @brief Converts a Quaternion to an euler-angle Vector3.
    /// 
    /// @param rotation The euler rotation vector.
    /// @returns A rotation Quaternion equivalent to the given axis-angle rotation.
    [[nodiscard]]
    static Vector3 ToEuler(const Quaternion& rotation) noexcept;
    
    /// @brief Converts a Quaternion to an euler-angle Vector3.
    /// 
    /// @param rotation The rotation quaternion.
    /// @param result The output value.
    /// @see ToEuler(const Quaternion&)
    static void ToEuler(const Quaternion& rotation, Vector3* result) noexcept;

    /// @brief Compute the dot product of two Quaternions.
    /// 
    /// @param a The left-hand side argument.
    /// @param b The right-hand side argument.
    /// @returns The result of @p a · @p b.
    [[nodiscard]]
    static constexpr float_t Dot(const Quaternion& a, const Quaternion& b) noexcept;
    
    /// @brief Compute the linear interpolation between two Quaternions.
    /// 
    /// @param value The current position.
    /// @param target The target position.
    /// @param t The time to lerp.
    /// @returns The lerp position.
    [[nodiscard]]
    static Quaternion Lerp(const Quaternion& value, const Quaternion& target, float_t t) noexcept;
    
    /// @brief Compute the linear interpolation between two Quaternions.
    /// 
    /// @param value The current position.
    /// @param target The target position.
    /// @param t The time to lerp.
    /// @param result The output value.
    /// @see Lerp(const Quaternion&, const Quaternion&, float_t)
    static void Lerp(const Quaternion& value, const Quaternion& target, float_t t, Quaternion* result) noexcept;
    
    /// @brief Compute the spherical linear interpolation between two Quaternions.
    /// 
    /// @param value The current position.
    /// @param target The target position.
    /// @param t The time to slerp.
    /// @returns The slerp position.
    [[nodiscard]]
    static Quaternion Slerp(const Quaternion& value, const Quaternion& target, float_t t) noexcept;
    
    /// @brief Compute the spherical linear interpolation between two Quaternions.
    /// 
    /// @param value The current position.
    /// @param target The target position.
    /// @param t The time to slerp.
    /// @param result The output value.
    /// 
    /// @see Slerp(const Quaternion&, const Quaternion&, float_t)
    static void Slerp(const Quaternion& value, const Quaternion& target, float_t t, Quaternion* result) noexcept;
    
    /// @brief Rotate a point using a rotation quaternion.
    /// 
    ///	Calling this function is equivalent to doing:
    ///	@code
    ///	rotation * point * rotation.Conjugate()
    ///	@endcode
    ///	
    /// @param point The current position.
    /// @param rotation The target position.
    /// @returns The rotated point.
    [[nodiscard]]
    static constexpr Vector3 Rotate(const Vector3& point, const Quaternion& rotation) noexcept;
    
    /// @brief Rotate a point using a rotation quaternion.
    /// 
    ///	Calling this function is equivalent to doing:
    ///	@code
    ///	rotation * point * rotation.Conjugate()
    ///	@endcode
    ///	
    /// @param point The current position.
    /// @param rotation The target position.
    /// @param result The output value.
    /// 
    /// @see Rotate(const Vector3&, const Quaternion&)
    static constexpr void Rotate(const Vector3& point, const Quaternion& rotation, Vector3* result) noexcept;

    /// @brief Construct a Quaternion with everything set to @c 0.
    constexpr Quaternion() = default;
    
    /// @brief Construct a Quaternion from a Vector4.
    constexpr explicit Quaternion(const Vector4& values) noexcept;

    /// @brief Construct a Quaternion from an imaginary and a real part.
    constexpr explicit Quaternion(const Vector3& imaginary, float_t real = 1.f) noexcept;

    /// @brief Construct a Quaternion with all its values set to @p xyzw.
    constexpr explicit Quaternion(float_t xyzw) noexcept;
    
    /// @brief  Constructs a Vector2 with its components set to the data pointed by <code>data</code>.
    /// 
    /// This constructor assumes that <code>data</code> is a valid pointer pointing to at least 2 float_t values.
    /// 
    /// @param data The data where the values for this vector's components are located.
    constexpr explicit Quaternion(const float_t* data) noexcept;

    /// @brief Construct a Quaternion from 4 @c float_t values.
    constexpr Quaternion(float_t x, float_t y, float_t z, float_t w) noexcept;

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

    /// @brief Returns a copy of the @c x component of this Quaternion.
    [[nodiscard]]
    constexpr float_t X() const noexcept;

    /// @brief Returns a copy of the @c y component of this Quaternion.
    [[nodiscard]]
    constexpr float_t Y() const noexcept;

    /// @brief Returns a copy of the @c z component of this Quaternion.
    [[nodiscard]]
    constexpr float_t Z() const noexcept;

    /// @brief Returns a copy of the @c w component of this Quaternion.
    [[nodiscard]]
    constexpr float_t W() const noexcept;

    /// @brief Returns a reference to the @c x component of this Quaternion.
    [[nodiscard]]
    constexpr float_t& X() noexcept;

    /// @brief Returns a reference to the @c y component of this Quaternion.
    [[nodiscard]]
    constexpr float_t& Y() noexcept;

    /// @brief Returns a reference to the @c z component of this Quaternion.
    [[nodiscard]]
    constexpr float_t& Z() noexcept;

    /// @brief Returns a reference to the @c w component of this Quaternion.
    [[nodiscard]]
    constexpr float_t& W() noexcept;

    /// @brief Computes the conjugate of this Quaternion.
    ///
    /// The conjugate of a Quaternion is one with the opposite of its imaginary part. 
    [[nodiscard]]
    constexpr Quaternion Conjugate() const noexcept;

    /// @brief Computes the conjugate of this Quaternion.
    ///
    /// The conjugate of a Quaternion is one with the opposite of its imaginary part.
    constexpr void Conjugate(Quaternion* result) const noexcept;

    /// @brief Returns a normalized version of this Quaternion.
    [[nodiscard]]
    Quaternion Normalized() const noexcept;

    /// @brief Returns a normalized version of this Quaternion.
    void Normalized(Quaternion* result) const noexcept;
    
    /// @brief Returns the length of this Quaternion.
    [[nodiscard]]
    float_t Length() const noexcept;

    /// @brief Returns the squared length of this Quaternion.
    [[nodiscard]]
    constexpr float_t SquaredLength() const noexcept;

    /// @brief Check whether all of this vector's components are infinite.
    [[nodiscard]]
    bool_t IsInfinity() const noexcept;

    /// @brief Check whether all of this vector's components are NaN.
    [[nodiscard]]
    bool_t IsNaN() const noexcept;
    
    /// @brief Returns an inverted version of this Quaternion.
    [[nodiscard]]
    constexpr Quaternion Inverted() const noexcept;

    /// @brief Returns an inverted version of this Quaternion.
    constexpr void Inverted(Quaternion* result) const noexcept;

    /// @brief Retrieves this vector's component at index i.
    /// 
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr float_t operator[](size_t i) const;
    
    /// @brief Retrieves this vector's component at index i.
    /// 
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr float_t& operator[](size_t i);
    
    /// @brief Converts this Quaternion to a Vector3 by returning its imaginary part.
    constexpr explicit operator Vector3() const noexcept;

    /// @brief Converts this Quaternion to a Vector4.
    constexpr explicit operator Vector4() const noexcept;
};

static_assert(std::is_default_constructible_v<Quaternion>, "Class Quaternion must be default constructible.");
static_assert(std::is_copy_constructible_v<Quaternion>, "Class Quaternion must be copy constructible.");
static_assert(std::is_move_constructible_v<Quaternion>, "Class Quaternion must be move constructible.");
static_assert(std::is_copy_assignable_v<Quaternion>, "Class Quaternion must be copy assignable.");
static_assert(std::is_move_assignable_v<Quaternion>, "Class Quaternion must be move assignable.");

constexpr Quaternion::Quaternion(const Vector4& values) noexcept : imaginary(values.x, values.y, values.z), real(values.w) {}

constexpr Quaternion::Quaternion(const Vector3& imaginary, const float_t real) noexcept : imaginary(imaginary), real(real) {}

constexpr Quaternion::Quaternion(const float_t xyzw) noexcept : imaginary(xyzw), real(xyzw) {}

constexpr Quaternion::Quaternion(const float_t* const data) noexcept : imaginary(data), real(data[3]) {}

constexpr Quaternion::Quaternion(const float_t x, const float_t y, const float_t z, const float_t w) noexcept : imaginary(x, y, z), real(w) {}

constexpr Quaternion Quaternion::Zero() noexcept { return Quaternion(); }

constexpr void Quaternion::Zero(Quaternion* result) noexcept { *result = Quaternion(); }

constexpr Quaternion Quaternion::UnitX() noexcept { return Quaternion(1.f, 0.f, 0.f, 0.f); }

constexpr void Quaternion::UnitX(Quaternion* result) noexcept { *result = Quaternion(1.f, 0.f, 0.f, 0.f); }

constexpr Quaternion Quaternion::UnitY() noexcept { return Quaternion(0.f, 1.f, 0.f, 0.f); }

constexpr void Quaternion::UnitY(Quaternion* result) noexcept { *result = Quaternion(0.f, 1.f, 0.f, 0.f); }

constexpr Quaternion Quaternion::UnitZ() noexcept { return Quaternion(0.f, 0.f, 1.f, 0.f); }

constexpr void Quaternion::UnitZ(Quaternion* result) noexcept { *result = Quaternion(0.f, 0.f, 1.f, 0.f); }

constexpr Quaternion Quaternion::UnitW() noexcept { return Quaternion(0.f, 0.f, 0.f, 1.f); }

constexpr void Quaternion::UnitW(Quaternion* result) noexcept { *result = Quaternion(0.f, 0.f, 0.f, 1.f); }

constexpr Quaternion Quaternion::Identity() noexcept { return UnitW(); }

constexpr void Quaternion::Identity(Quaternion* result) noexcept { *result = UnitW(); }

constexpr float_t Quaternion::Dot(const Quaternion& a, const Quaternion& b) noexcept { return a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z() + a.W() * b.W(); }

constexpr const float_t* Quaternion::Data() const noexcept { return &imaginary.x; }

constexpr float_t* Quaternion::Data() noexcept { return &imaginary.x; }

constexpr float_t& Quaternion::X() noexcept { return imaginary.x; }

constexpr float_t& Quaternion::Y() noexcept { return imaginary.y; }

constexpr float_t& Quaternion::Z() noexcept { return imaginary.z; }

constexpr float_t& Quaternion::W() noexcept { return real; }

constexpr float_t Quaternion::X() const noexcept { return imaginary.x; }

constexpr float_t Quaternion::Y() const noexcept { return imaginary.y; }

constexpr float_t Quaternion::Z() const noexcept { return imaginary.z; }

constexpr float_t Quaternion::W() const noexcept { return real; }

constexpr Quaternion Quaternion::Conjugate() const noexcept { return Quaternion(-imaginary, real); }

constexpr void Quaternion::Conjugate(Quaternion* result) const noexcept { *result = Quaternion(-imaginary, real); }

constexpr float_t Quaternion::SquaredLength() const noexcept { return SQ(imaginary.x) + SQ(imaginary.y) + SQ(imaginary.z) + SQ(real); }

constexpr float_t Quaternion::operator[](const size_t i) const
{
    if (i < 4) [[likely]]
        return *(Data() + i);
    [[unlikely]]
        throw std::out_of_range("Quaternion subscript out of range");
}

constexpr float_t& Quaternion::operator[](const size_t i)
{
    if (i < 4) [[likely]]
        return *(Data() + i);
    [[unlikely]]
        throw std::out_of_range("Quaternion subscript out of range");
}

constexpr Quaternion::operator Vector3() const noexcept { return imaginary; }

constexpr Quaternion::operator Vector4() const noexcept { return Vector4(imaginary.x, imaginary.y, imaginary.z, real); }

/// @brief Adds two @ref Quaternion "Quaternions" together.
[[nodiscard]]
constexpr Quaternion operator+(const Quaternion& a, const Quaternion& b) noexcept { return Quaternion(a.imaginary + b.imaginary, a.real + b.real); }

/// @brief Returns the opposite of a Quaternion.
///
/// This effectively means replacing all values of this Quaternion with their opposite.
[[nodiscard]]
constexpr Quaternion operator-(const Quaternion& a) noexcept { return Quaternion(-a.imaginary, -a.real); }

/// @brief Subtracts a Quaternion from another one.
[[nodiscard]]
constexpr Quaternion operator-(const Quaternion& a, const Quaternion& b) noexcept { return Quaternion(a + -b); }

/// @brief Multiplies two @ref Quaternion "Quaternions" together.
[[nodiscard]]
constexpr Quaternion operator*(const Quaternion& a, const Quaternion& b) noexcept
{
    Quaternion result;

    // cross(av, bv)
    const float_t cx = a.Y() * b.Z() - a.Z() * b.Y();
    const float_t cy = a.Z() * b.X() - a.X() * b.Z();
    const float_t cz = a.X() * b.Y() - a.Y() * b.X();

    const float_t dot = a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();

    result.X() = a.X() * b.W() + b.X() * a.W() + cx;
    result.Y() = a.Y() * b.W() + b.Y() * a.W() + cy;
    result.Z() = a.Z() * b.W() + b.Z() * a.W() + cz;
    result.W() = a.W() * b.W() - dot;

    return result;
}

/// @brief Multiplies a Quaternion with a Vector3.
[[nodiscard]]
constexpr Quaternion operator*(const Quaternion& q, const Vector3& v) noexcept { return q * Quaternion(v, 1.f); }

/// @brief Multiplies a Quaternion by a @p factor.
[[nodiscard]]
constexpr Quaternion operator*(const Quaternion& q, const float_t factor) noexcept { return Quaternion(q.imaginary * factor, q.real * factor); }

/// @brief Multiplies a Quaternion by a @p factor.
[[nodiscard]]
constexpr Quaternion operator*(const float_t factor, const Quaternion q) noexcept { return q * factor; }

/// @brief Divides a Quaternion by a @p factor.
[[nodiscard]]
constexpr Quaternion operator/(const Quaternion& v, const float_t factor) noexcept { return Quaternion(v.imaginary / factor, v.real / factor); }

/// @brief Adds two @ref Quaternion "Quaternions" according to @ref operator+(const Quaternion&, const Quaternion&), placing the result in @p a.
constexpr Quaternion& operator+=(Quaternion& a, const Quaternion& b) noexcept { return a = a + b; }

/// @brief Subtracts two @ref Quaternion "Quaternions" according to @ref operator-(const Quaternion&, const Quaternion&), placing the result in @p a.
constexpr Quaternion& operator-=(Quaternion& a, const Quaternion& b) noexcept { return a = a - b; }

/// @brief Multiplies two @ref Quaternion "Quaternions" according to @ref operator*(const Quaternion&, const Quaternion&), placing the result in @p a.
constexpr Quaternion& operator*=(Quaternion& a, const Quaternion& b) noexcept { return a = a * b; }

/// @brief Multiplies a Quaternion by a factor according to @ref operator*(const Quaternion&, const float_t), placing the result in @p a.
constexpr Quaternion& operator*=(Quaternion& q, const float_t factor) noexcept { return q = q * factor; }

/// @brief Divides a Quaternion by a factor according to @ref operator/(const Quaternion&, const float_t), placing the result in @p a.
constexpr Quaternion& operator/=(Quaternion& q, const float_t factor) noexcept { return q = q / factor; }

/// @brief Checks if two Quaternions are considered equal.
[[nodiscard]]
constexpr bool operator==(const Quaternion& a, const Quaternion& b)
{
    return a.imaginary.x == b.imaginary.x
        && a.imaginary.y == b.imaginary.y
        && a.imaginary.z == b.imaginary.z
        && a.real == b.real;
}

/// @brief Checks if two Quaternions are considered equal.
[[nodiscard]]
constexpr bool operator!=(const Quaternion& a, const Quaternion& b) { return !(a == b); }

/// @brief Streams a Quaternion into @p out, printing its values one by one on a single line.
MATH_TOOLBOX std::ostream& operator<<(std::ostream& out, const Quaternion& q);

constexpr Quaternion Quaternion::Inverted() const noexcept
{
    Quaternion result;
    Inverted(&result);
    return result;
}

constexpr void Quaternion::Inverted(Quaternion* result) const noexcept
{
    const float_t sqLength = SquaredLength();
    
    if (Calc::IsZero(sqLength))
    {
        *result = Zero();
        return;
    }
    
    *result = Conjugate() / sqLength;
}

constexpr Vector3 Quaternion::Rotate(const Vector3& point, const Quaternion& rotation) noexcept { return (rotation * point * rotation.Conjugate()).imaginary; }

constexpr void Quaternion::Rotate(const Vector3& point, const Quaternion& rotation, Vector3* result) noexcept { *result = (rotation * point * rotation.Conjugate()).imaginary; }

template <>
struct std::formatter<Quaternion>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Quaternion q, FmtContext& ctx) const;

private:
    std::string m_Format;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Quaternion, char_t>::parse(ParseContext& ctx)
{
    auto it = ctx.begin();
    if (it == ctx.end())
        return it;

    while (*it != '}' && it != ctx.end())
        m_Format += *it++;

    return it;
}

template <class FmtContext>
typename FmtContext::iterator std::formatter<Quaternion>::format(Quaternion q, FmtContext &ctx) const
{
    std::ostringstream out;

    out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(q.X(), q.Y(), q.Z(), q.W()));

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
