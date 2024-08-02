#pragma once

#include <format>
#include <sstream>

#include <ostream>

#include "Maths/calc.hpp"
#include "Maths/quaternion.hpp"
#include "Maths/vector3.hpp"

/// @file matrix3.hpp
/// @brief Defines the Matrix3 class.

/// @brief The Matrix3 class represents a 3x3 array mainly used for mathematical operations.
/// 
/// Matrices are stored using the column-major convention.
class MATH_TOOLBOX Matrix3
{
public:
    /// @brief The component at position [0, 0] of a Matrix3.
    float_t m00 = 0.f;
    
    /// @brief The component at position [1, 0] of a Matrix3.
    float_t m10 = 0.f;
    
    /// @brief The component at position [2, 0] of a Matrix3.
    float_t m20 = 0.f;
    
    /// @brief The component at position [0, 1] of a Matrix3.
    float_t m01 = 0.f;
    
    /// @brief The component at position [1, 1] of a Matrix3.
    float_t m11 = 0.f;
    
    /// @brief The component at position [2, 1] of a Matrix3.
    float_t m21 = 0.f;
    
    /// @brief The component at position [0, 2] of a Matrix3.
    float_t m02 = 0.f;
    
    /// @brief The component at position [1, 2] of a Matrix3.
    float_t m12 = 0.f;
    
    /// @brief The component at position [2, 2] of a Matrix3.
    float_t m22 = 0.f;

    /// @brief Returns the identity %Matrix.
    /// 
    /// The identity %Matrix is one with its diagonal set to one and everything else set to zero.
    [[nodiscard]]
    static constexpr Matrix3 Identity() noexcept;

    /// @brief Returns the identity %Matrix.
    /// 
    /// The identity %Matrix is one with its diagonal set to one and everything else set to zero.
    static constexpr void Identity(Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix from the given angle and axis.
    /// 
    /// @param angle The angle in radians.
    /// @param axis The axis around which the rotation occurs.
    [[nodiscard]]
    static Matrix3 Rotation(float_t angle, const Vector3& axis) noexcept;

    /// @brief Creates a 3D rotation %Matrix from the given angle and axis.
    /// 
    /// @param angle The angle in radians.
    /// @param axis The axis around which the rotation occurs.
    /// @param result The output of the function.
    static void Rotation(float_t angle, const Vector3& axis, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the X axis from the given angle.
    /// 
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix3 RotationX(float_t angle) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the X axis from the given angle.
    /// 
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationX(float_t angle, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the X axis from the given angle.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static constexpr Matrix3 RotationX(float_t cos, float_t sin) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the X axis from the given angle.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationX(float_t cos, float_t sin, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Y axis from the given angle.
    /// 
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix3 RotationY(float_t angle) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Y axis from the given angle.
    /// 
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationY(float_t angle, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Y axis from the given angle.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static constexpr Matrix3 RotationY(float_t cos, float_t sin) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Y axis from the given angle.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationY(float_t cos, float_t sin, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Z axis from the given angle.
    /// 
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix3 RotationZ(float_t angle) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Z axis from the given angle.
    /// 
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationZ(float_t angle, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Z axis from the given angle.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static constexpr Matrix3 RotationZ(float_t cos, float_t sin) noexcept;

    /// @brief Creates a 3D rotation %Matrix around the Z axis from the given angle.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationZ(float_t cos, float_t sin, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix from the given angle for each of the x, y, and z axis.
    [[nodiscard]]
    static Matrix3 Rotation(const Vector3& rotation) noexcept;

    /// @brief Creates a 3D rotation %Matrix from the given angle for each of the x, y, and z axis.
    static void Rotation(const Vector3& rotation, Matrix3* result) noexcept;

    /// @brief	Creates a 3D rotation %Matrix from the given rotation Quaternion.
    [[nodiscard]]
    static constexpr Matrix3 Rotation(const Quaternion& rotation) noexcept;

    /// @brief	Creates a 3D rotation %Matrix from the given rotation Quaternion.
    static constexpr void Rotation(const Quaternion& rotation, Matrix3* result) noexcept;

    /// @brief Creates a 3D rotation %Matrix from the given cosine, sine and axis.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param axis The axis around which the rotation occurs.
    [[nodiscard]]
    static Matrix3 Rotation(float_t cos, float_t sin, const Vector3& axis) noexcept;

    /// @brief Creates a 3D rotation %Matrix from the given cosine, sine and axis.
    /// 
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param axis The axis around which the rotation occurs.
    /// @param result The output of the function.
    static void Rotation(float_t cos, float_t sin, const Vector3& axis, Matrix3* result) noexcept;

    /// @brief Creates a 3D scaling %Matrix from the given Vector3.
    [[nodiscard]]
    static constexpr Matrix3 Scaling(const Vector3& scale) noexcept;

    /// @brief Creates a 3D scaling %Matrix from the given Vector3.
    static constexpr void Scaling(const Vector3& scale, Matrix3* result) noexcept;

    /// @brief Creates a Matrix3 with all its values set to 0.
    constexpr Matrix3() = default;

    /// @brief Creates a Matrix3 with all its values set to this default value.
    constexpr explicit Matrix3(float_t defaultValue) noexcept;

    /// @brief Constructs a Matrix3 with its components set to the data pointed by @c data.
    /// 
    /// This constructor assumes that @c data is a valid pointer pointing to at least 9 @c float_t values.
    /// 
    /// @param data The data where the values for this matrix's components are located.
    constexpr explicit Matrix3(const float_t* data) noexcept;

    /// @brief Constructs a Matrix3 with 3 column vectors.
    constexpr Matrix3(
            const Vector3& c0,
            const Vector3& c1,
            const Vector3& c2
    ) noexcept;

    /// @brief Constructs a Matrix3 with 16 float_t values.
    constexpr Matrix3(
            float_t m00, float_t m01, float_t m02,
            float_t m10, float_t m11, float_t m12,
            float_t m20, float_t m21, float_t m22
    ) noexcept;

    /// @brief Gets a pointer to the first value of this Matrix3.
    /// 
    /// @returns A pointer to the first value of this Matrix3.
    [[nodiscard]]
    constexpr const float_t* Raw() const noexcept;

    /// @brief Gets a pointer to the first value of this Matrix3.
    /// 
    /// @returns A pointer to the first value of this Matrix3.
    [[nodiscard]]
    constexpr float_t* Raw() noexcept;

    /// @brief Uses the @c std::cout stream to print the values of this matrix in a square-like shape, e.g. by using newlines to make it easier to read.
    void DebugPrint() const noexcept;

    /// @brief Returns whether the Matrix3 has everything except its diagonal set to zero.
    [[nodiscard]]
    constexpr bool_t IsDiagonal() const noexcept;

    /// @brief Returns whether the Matrix3 is the identity matrix.
    /// 
    /// If this returns true, Matrix3::Identity() == *this should be true.
    [[nodiscard]]
    constexpr bool_t IsIdentity() const noexcept;

    /// @brief Returns whether this Matrix3 has everything set to zero.
    [[nodiscard]]
    constexpr bool_t IsNull() const noexcept;

    /// @brief Returns whether the Matrix3 is symmetric by its diagonal elements.
    [[nodiscard]]
    constexpr bool_t IsSymmetric() const noexcept;

    /// @brief Returns whether the Matrix3 is symmetric by its diagonal elements but one of the sides is the opposite of the other.
    [[nodiscard]]
    constexpr bool_t IsAntisymmetric() const noexcept;

    /// @brief Returns the diagonal elements of the Matrix3.
    [[nodiscard]]
    constexpr Vector3 Diagonal() const noexcept;

    /// @brief Returns the diagonal elements of the Matrix3.
    constexpr void Diagonal(Vector3* result) const noexcept;

    /// @brief Returns the sum of the diagonal elements of the Matrix3.
    [[nodiscard]]
    constexpr float_t Trace() const noexcept;

    /// @brief Returns the determinant of this Matrix3.
    [[nodiscard]]
    constexpr float_t Determinant() const noexcept;

    /// @brief Switches the Matrix3 by its diagonal elements.
    [[nodiscard]]
    constexpr Matrix3 Transposed() const noexcept;

    /// @brief Switches the Matrix3 by its diagonal elements.
    constexpr void Transposed(Matrix3* result) const noexcept;

    /// @brief Computes the invert of this Matrix3, e.g. @c *this * Inverted() == Identity() is true.
    [[nodiscard]]
    constexpr Matrix3 Inverted() const;

    /// @brief Computes the invert of this Matrix3, e.g. @c *this * Inverted() == Identity() is true.
    constexpr void Inverted(Matrix3* result) const;

    /// @brief Retrieves this matrix's value at position @c [col, row].
    /// 
    /// @param row The index of the col to get.
    /// @param col The index of the column to get.
    /// @returns The value at position @c [col, row].
    [[nodiscard]]
    constexpr float_t At(size_t row, size_t col) const;

    /// @brief Retrieves this matrix's col at position @c [col, row].
    /// 
    /// @param row The index of the col to get.
    /// @param col The index of the column to get.
    /// @returns The value at position @c [col, row].
    [[nodiscard]]
    constexpr float_t& At(size_t row, size_t col);

    /// @brief	Retrieves this matrix's column vector at position @c col.
    /// 
    ///	If you want to get a value of this matrix, consider using <see cref="At(size_t, size_t)"/>
    ///	instead, as it is optimized for direct-value access.
    ///	
    /// @param col The index of the column to get.
    /// @returns The column vector at index @c col.
    [[nodiscard]]
    constexpr Vector3 operator[](size_t col) const;

    /// @brief	Retrieves this matrix's column vector at position @c col.
    /// 
    ///	If you want to get a value of this matrix, consider using <see cref="At(size_t, size_t)"/>
    ///	instead, as it is optimized for direct-value access.
    ///	
    /// @param col The index of the column to get.
    /// @returns The column vector at index @c col.
    [[nodiscard]]
    constexpr Vector3& operator[](size_t col);

    /// @brief Converts this Matrix3 to a Matrix, homogenizing the new row and column.
    [[nodiscard]]
    explicit operator Matrix() const;
};

static_assert(std::is_default_constructible_v<Matrix3>, "Class Matrix3 must be default constructible.");
static_assert(std::is_copy_constructible_v<Matrix3>, "Class Matrix3 must be copy constructible.");
static_assert(std::is_move_constructible_v<Matrix3>, "Class Matrix3 must be move constructible.");
static_assert(std::is_copy_assignable_v<Matrix3>, "Class Matrix3 must be copy assignable.");
static_assert(std::is_move_assignable_v<Matrix3>, "Class Matrix3 must be move assignable.");

constexpr Matrix3::Matrix3(const float_t defaultValue) noexcept
    : m00(defaultValue), m10(defaultValue), m20(defaultValue)
    , m01(defaultValue), m11(defaultValue), m21(defaultValue)
    , m02(defaultValue), m12(defaultValue), m22(defaultValue)
{
}

constexpr Matrix3::Matrix3(const float_t* const data) noexcept
    : m00(data[0]), m10(data[1]), m20(data[2])
    , m01(data[3]), m11(data[4]), m21(data[5])
    , m02(data[6]), m12(data[7]), m22(data[8])
{
}

constexpr Matrix3::Matrix3(const Vector3& c0, const Vector3& c1, const Vector3& c2) noexcept
    : m00(c0.x), m10(c1.x), m20(c2.x)
    , m01(c0.y), m11(c1.y), m21(c2.y)
    , m02(c0.z), m12(c1.z), m22(c2.z)
{
}

constexpr Matrix3::Matrix3(
    const float_t m00, const float_t m01, const float_t m02,
    const float_t m10, const float_t m11, const float_t m12,
    const float_t m20, const float_t m21, const float_t m22
) noexcept
    : m00(m00), m10(m10), m20(m20)
    , m01(m01), m11(m11), m21(m21)
    , m02(m02), m12(m12), m22(m22)
{
}

/// @brief Returns the opposite of a Matrix3.
///
/// This effectively means replacing all values of this Matrix3 with their opposite.
[[nodiscard]]
constexpr Matrix3 operator-(const Matrix3& matrix) noexcept
{
    return Matrix3(
        -matrix.m00, -matrix.m01, -matrix.m02,
        -matrix.m10, -matrix.m11, -matrix.m12,
        -matrix.m20, -matrix.m21, -matrix.m22
    );
}

/// @brief Adds the values of two @ref Matrix3 "3x3 Matrices" one by one.
[[nodiscard]]
constexpr Matrix3 operator+(const Matrix3& m1, const Matrix3& m2) noexcept
{
    return Matrix3(
        m1.m00 + m2.m00, m1.m01 + m2.m01, m1.m02 + m2.m02,
        m1.m10 + m2.m10, m1.m11 + m2.m11, m1.m12 + m2.m12,
        m1.m20 + m2.m20, m1.m21 + m2.m21, m1.m22 + m2.m22
    );
}

/// @brief Subtracts the values of two @ref Matrix3 "Matrices" one by one.
[[nodiscard]]
constexpr Matrix3 operator-(const Matrix3& m1, const Matrix3& m2) noexcept { return m1 + -m2; }

/// @brief Multiplies all values of a Matrix by a @p scalar.
[[nodiscard]]
constexpr Matrix3 operator*(const Matrix3& m, const float_t scalar) noexcept
{
    return Matrix3(
        m.m00 * scalar, m.m01 * scalar, m.m02 * scalar,
        m.m10 * scalar, m.m11 * scalar, m.m12 * scalar,
        m.m20 * scalar, m.m21 * scalar, m.m22 * scalar
    );
}

/// @brief Multiplies all values of a Matrix by a @p scalar.
[[nodiscard]]
constexpr Matrix3 operator*(const float_t factor, const Matrix3& m) noexcept { return m * factor; }

/// @brief Multiplies a Vector2 by a Matrix3.
[[nodiscard]]
constexpr Vector2 operator*(const Matrix3& m, const Vector2& v) noexcept
{
    return Vector2(
        v.x * m.m00 + v.y * m.m01 + m.m02,
        v.x * m.m10 + v.y * m.m11 + m.m12
    );
}

/// @brief Multiplies a Vector3 by a Matrix3.
[[nodiscard]]
constexpr Vector3 operator*(const Matrix3& m, const Vector3& v) noexcept
{
    return Vector3(
        v.x * m.m00 + v.y * m.m01 + v.z * m.m02,
        v.x * m.m10 + v.y * m.m11 + v.z * m.m12,
        v.x * m.m20 + v.y * m.m21 + v.z * m.m22
    );
}

/// @brief Multiplies two @ref Matrix3 "Matrices".
[[nodiscard]]
constexpr Matrix3 operator*(const Matrix3& m1, const Matrix3& m2) noexcept
{
    return Matrix3(
        m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20,
        m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21,
        m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22,
        
        m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20,
        m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21,
        m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22,
        
        m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20,
        m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21,
        m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22
    );
}

/// @brief Adds two @ref Matrix3 "Matrices" according to @ref operator+(const Matrix&, const Matrix&), placing the result in @p m1.
constexpr Matrix3& operator+=(Matrix3& m1, const Matrix3& m2) noexcept { return m1 = m1 + m2; }

/// @brief Subtracts two @ref Matrix3 "Matrices" according to @ref operator-(const Matrix&, const Matrix&), placing the result in @p m1.
constexpr Matrix3& operator-=(Matrix3& m1, const Matrix3& m2) noexcept { return m1 = m1 - m2; }

/// @brief Multiplies a Matrix by a @p scalar according to @ref operator*(const Matrix&, const float_t), placing the result in @p m.
constexpr Matrix3& operator*=(Matrix3& m, const float_t scalar) noexcept { return m = m * scalar; }

/// @brief Multiplies a Matrix by a Vector2 according to @ref operator*(const Matrix&, const Vector2&), placing the result in @p m.
constexpr Vector2& operator*=(const Matrix3& m, Vector2& v) noexcept { return v = m * v; }

/// @brief Multiplies a Matrix by a Vector3 according to @ref operator*(const Matrix&, const Vector3&), placing the result in @p m.
constexpr Vector3& operator*=(const Matrix3& m, Vector3& v) noexcept { return v = m * v; }

/// @brief Multiplies two @ref Matrix3 "Matrices" according to @ref operator*(const Matrix&, const Matrix&), placing the result in @p m1.
constexpr Matrix3& operator*=(Matrix3& m1, const Matrix3& m2) noexcept { return m1 = m1 * m2; }

/// @brief	Checks if two Matrices are equal.
[[nodiscard]]
constexpr bool_t operator==(const Matrix3& a, const Matrix3& b)
{
    return a.m00 == b.m00 && a.m01 == b.m01 && a.m02 == b.m02
        && a.m10 == b.m10 && a.m11 == b.m11 && a.m12 == b.m12
        && a.m20 == b.m20 && a.m21 == b.m21 && a.m22 == b.m22;
}

/// @brief Checks if two Matrices are different.
[[nodiscard]]
constexpr bool_t operator!=(const Matrix3& a, const Matrix3& b) { return !(a == b); }

constexpr Matrix3 Matrix3::Identity() noexcept
{
    return Matrix3(
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    );
}

constexpr void Matrix3::Identity(Matrix3* result) noexcept
{
    *result = Matrix3(
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    );
}

constexpr Matrix3 Matrix3::RotationX(const float_t cos, const float_t sin) noexcept
{
    return Matrix3(
        1.f,    0.f,    0.f,
        0.f,    cos,   -sin,
        0.f,    sin,    cos
    );
}

constexpr void Matrix3::RotationX(const float_t cos, const float_t sin, Matrix3* result) noexcept
{
    *result = Matrix3(
        1.f,    0.f,    0.f,
        0.f,    cos,   -sin,
        0.f,    sin,    cos
    );
}

constexpr Matrix3 Matrix3::RotationY(const float_t cos, const float_t sin) noexcept
{
    return Matrix3(
        cos,    0.f,    sin,
        0.f,    1.f,    0.f,
        -sin,   0.f,    cos
    );
}

constexpr void Matrix3::RotationY(const float_t cos, const float_t sin, Matrix3* result) noexcept
{
    *result = Matrix3(
        cos,    0.f,    sin,
        0.f,    1.f,    0.f,
        -sin,   0.f,    cos
    );
}

constexpr Matrix3 Matrix3::RotationZ(const float_t cos, const float_t sin) noexcept
{
    return Matrix3(
        cos,   -sin,    0.f,
        sin,    cos,    0.f,
        0.f,    0.f,    1.f
    );
}

constexpr void Matrix3::RotationZ(const float_t cos, const float_t sin, Matrix3* result) noexcept
{
    *result = Matrix3(
        cos,   -sin,    0.f,
        sin,    cos,    0.f,
        0.f,    0.f,    1.f
    );
}

constexpr Matrix3 Matrix3::Rotation(const Quaternion& rotation) noexcept
{
    Matrix3 result;
    Rotation(rotation, &result);
    return result;
}

constexpr void Matrix3::Rotation(const Quaternion& rotation, Matrix3* result) noexcept
{
    const float_t xx = SQ(rotation.X());
    const float_t yy = SQ(rotation.Y());
    const float_t zz = SQ(rotation.Z());

    const float_t xy = rotation.X() * rotation.Y();
    const float_t wz = rotation.Z() * rotation.W();
    const float_t xz = rotation.Z() * rotation.X();
    const float_t wy = rotation.Y() * rotation.W();
    const float_t yz = rotation.Y() * rotation.Z();
    const float_t wx = rotation.X() * rotation.W();

    *result = Matrix3(
        1.f - 2.f * (yy + zz), 2.f * (xy - wz), 2.f * (xz + wy),
        2.f * (xy + wz), 1.f - 2.f * (zz + xx), 2.f * (yz - wx),
        2.f * (xz - wy), 2.f * (yz + wx), 1.f - 2.f * (yy + xx)
    );
}

constexpr Matrix3 Matrix3::Scaling(const Vector3 &scale) noexcept
{
    return Matrix3(
        scale.x,     0.f,     0.f,
        0.f,     scale.y,     0.f,
        0.f,         0.f, scale.z
    );
}

constexpr void Matrix3::Scaling(const Vector3& scale, Matrix3* result) noexcept
{
    *result = Matrix3(
        scale.x,     0.f,     0.f,
        0.f,     scale.y,     0.f,
        0.f,         0.f, scale.z
    );
}

constexpr const float_t* Matrix3::Raw() const noexcept { return &m00; }

constexpr float_t* Matrix3::Raw() noexcept { return &m00; }

constexpr bool_t Matrix3::IsDiagonal() const noexcept
{
    return                      Calc::IsZero(m01) && Calc::IsZero(m02)
        && Calc::IsZero(m10)                      && Calc::IsZero(m12)
        && Calc::IsZero(m20) && Calc::IsZero(m21);
}

constexpr bool_t Matrix3::IsIdentity() const noexcept
{
    if (!IsDiagonal())
        return false;

    return Calc::Equals(m00, 1.f) && Calc::Equals(m11, 1.f) && Calc::Equals(m22, 1.f);
}

constexpr bool_t Matrix3::IsNull() const noexcept
{
    if (!IsDiagonal())
        return false;

    return Calc::IsZero(m00) && Calc::IsZero(m11) && Calc::IsZero(m22);
}

constexpr bool_t Matrix3::IsSymmetric() const noexcept
{
    return Calc::Equals(m01, m10) && Calc::Equals(m02, m20)
           && Calc::Equals(m12, m21);
}

constexpr bool_t Matrix3::IsAntisymmetric() const noexcept
{
    return Calc::Equals(m01, -m10) && Calc::Equals(m02, -m20)
           && Calc::Equals(m12, -m21);
}

constexpr Vector3 Matrix3::Diagonal() const noexcept { return Vector3(m00, m11, m22); }

constexpr void Matrix3::Diagonal(Vector3* result) const noexcept { *result = Vector3(m00, m11, m22); }

constexpr float_t Matrix3::Trace() const noexcept { return m00 + m11 + m22; }

constexpr float_t Matrix3::Determinant() const noexcept
{
    return m00 * (m11 * m22 - m21 * m12)
         - m10 * (m12 * m20 - m22 * m10)
         + m20 * (m01 * m12 - m11 * m02);
}

constexpr Matrix3 Matrix3::Transposed() const noexcept
{
    return Matrix3(
        m00, m10, m20,
        m01, m11, m21,
        m02, m12, m22
    );
}

constexpr void Matrix3::Transposed(Matrix3* result) const noexcept
{
    *result = Matrix3(
        m00, m10, m20,
        m01, m11, m21,
        m02, m12, m22
    );
}

constexpr Matrix3 Matrix3::Inverted() const
{
    Matrix3 result;
    Inverted(&result);
    return result;
}

constexpr void Matrix3::Inverted(Matrix3* result) const
{
    const float_t determinant = Determinant();
    
    if (determinant == 0.f) [[unlikely]]
        throw std::invalid_argument("Matrix3 isn't invertible");

    *result = Matrix3(
        m11 * m22 - m12 * m21,
      -(m01 * m22 - m02 * m21),
        m01 * m12 - m02 * m11,

      -(m10 * m22 - m12 * m20),
        m00 * m22 - m02 * m20,
      -(m00 * m12 - m02 * m10),

        m10 * m21 - m11 * m20,
      -(m00 * m21 - m01 * m20),
        m00 * m11 - m01 * m10
    ) * (1.f / determinant);
}

constexpr float_t Matrix3::At(const size_t row, const size_t col) const
{
    if (row < 3 && col < 3) [[likely]]
        return Raw()[col * 3 + row];
    
    [[unlikely]]
    throw std::out_of_range("Matrix3 subscript out of range");
}

constexpr float_t& Matrix3::At(const size_t row, const size_t col)
{
    if (row < 3 && col < 3) [[likely]]
        return Raw()[col * 3 + row];
    
    [[unlikely]]
    throw std::out_of_range("Matrix3 subscript out of range");
}

constexpr Vector3 Matrix3::operator[](const size_t col) const
{
    return Vector3(Raw() + static_cast<ptrdiff_t>(col) * 3);
}

constexpr Vector3& Matrix3::operator[](const size_t col)
{
    // Pointer arithmetic magic to get around not being able to use reinterpret_cast
    return *static_cast<Vector3*>(static_cast<void*>(Raw() + static_cast<ptrdiff_t>(col) * 3));
}

/// @brief Streams a Matrix3 into @p out, printing its values one by one on a single line.
///
/// If you instead want a multiline print, you can use Matrix::DebugPrint.
MATH_TOOLBOX std::ostream& operator<<(std::ostream& out, const Matrix3& m);

template <>
struct std::formatter<Matrix3>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it == 'm')
        {
            m_Multiline = true;
            it++;
        }

        while (*it != '}' && it != ctx.end())
            m_Format += *it++;

        return it;
    }

    template <class FmtContext>
    typename FmtContext::iterator format(Matrix3 m, FmtContext& ctx) const
    {
        std::ostringstream out;

        const char_t separator = m_Multiline ? '\n' : ' ';

        out << std::vformat(
                "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]" + separator
                + "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]" + separator
                + "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]",
                std::make_format_args(
                        m.m00, m.m01, m.m02,
                        m.m10, m.m11, m.m12,
                        m.m20, m.m21, m.m22
                )
        );

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }

private:
    std::string m_Format;
    bool_t m_Multiline = false;
};
