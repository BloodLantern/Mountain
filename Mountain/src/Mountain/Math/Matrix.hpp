#pragma once

#include <format>
#include <sstream>
#include <ostream>

#include "Mountain/Math/Calc.hpp"
#include "Mountain/Math/Matrix3.hpp"
#include "Mountain/Math/Quaternion.hpp"
#include "Mountain/Math/Vector3.hpp"
#include "Mountain/Math/Vector4.hpp"

/// @file matrix.hpp
/// @brief Defines the Matrix struct.

/// @brief The Matrix struct represents a 4x4 array mainly used for mathematical operations.
///
/// Matrices are stored using the column-major convention.
struct MOUNTAIN_API Matrix
{
    /// @brief The component at position [0, 0] of a Matrix.
    f32 m00 = 0.f;

    /// @brief The component at position [1, 0] of a Matrix.
    f32 m10 = 0.f;

    /// @brief The component at position [2, 0] of a Matrix.
    f32 m20 = 0.f;

    /// @brief The component at position [3, 0] of a Matrix.
    f32 m30 = 0.f;

    /// @brief The component at position [0, 1] of a Matrix.
    f32 m01 = 0.f;

    /// @brief The component at position [1, 1] of a Matrix.
    f32 m11 = 0.f;

    /// @brief The component at position [2, 1] of a Matrix.
    f32 m21 = 0.f;

    /// @brief The component at position [3, 1] of a Matrix.
    f32 m31 = 0.f;

    /// @brief The component at position [0, 2] of a Matrix.
    f32 m02 = 0.f;

    /// @brief The component at position [1, 2] of a Matrix.
    f32 m12 = 0.f;

    /// @brief The component at position [2, 2] of a Matrix.
    f32 m22 = 0.f;

    /// @brief The component at position [3, 2] of a Matrix.
    f32 m32 = 0.f;

    /// @brief The component at position [0, 3] of a Matrix.
    f32 m03 = 0.f;

    /// @brief The component at position [1, 3] of a Matrix.
    f32 m13 = 0.f;

    /// @brief The component at position [2, 3] of a Matrix.
    f32 m23 = 0.f;

    /// @brief The component at position [3, 3] of a Matrix.
    f32 m33 = 0.f;

    /// @brief Returns the identity Matrix.
    ///
    /// The identity Matrix is one with its diagonal set to one and everything else set to zero.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Identity() noexcept;

    /// @brief Returns the identity Matrix.
    ///
    /// The identity Matrix is one with its diagonal set to one and everything else set to zero.
    static constexpr void Identity(Matrix* result) noexcept;

    /// @brief Creates a 3D translation Matrix from the given angle for each of the x, y, and z axis.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Translation(const Vector3& translation) noexcept;

    /// @brief Creates a 3D translation Matrix from the given angle for each of the x, y, and z axis.
    static constexpr void Translation(const Vector3& translation, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix from the given angle and axis.
    ///
    /// @param angle The angle in radians.
    /// @param axis The axis around which the rotation occurs.
    ATTRIBUTE_NODISCARD
    static Matrix Rotation(f32 angle, const Vector3& axis) noexcept;

    /// @brief Creates a 3D rotation Matrix from the given angle and axis.
    ///
    /// @param angle The angle in radians.
    /// @param axis The axis around which the rotation occurs.
    /// @param result The output of the function.
    static void Rotation(f32 angle, const Vector3& axis, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix around the X axis from the given angle.
    ///
    /// @param angle The angle in radians.
    ATTRIBUTE_NODISCARD
    static Matrix RotationX(f32 angle) noexcept;

    /// @brief Creates a 3D rotation Matrix around the X axis from the given angle.
    ///
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationX(f32 angle, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix around the X axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix RotationX(f32 cos, f32 sin) noexcept;

    /// @brief Creates a 3D rotation Matrix around the X axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationX(f32 cos, f32 sin, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Y axis from the given angle.
    ///
    /// @param angle The angle in radians.
    ATTRIBUTE_NODISCARD
    static Matrix RotationY(f32 angle) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Y axis from the given angle.
    ///
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationY(f32 angle, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Y axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix RotationY(f32 cos, f32 sin) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Y axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationY(f32 cos, f32 sin, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Z axis from the given angle.
    ///
    /// @param angle The angle in radians.
    ATTRIBUTE_NODISCARD
    static Matrix RotationZ(f32 angle) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Z axis from the given angle.
    ///
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationZ(f32 angle, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Z axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix RotationZ(f32 cos, f32 sin) noexcept;

    /// @brief Creates a 3D rotation Matrix around the Z axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationZ(f32 cos, f32 sin, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation Matrix from the given angle for each of the x, y, and z axis.
    ATTRIBUTE_NODISCARD
    static Matrix Rotation(const Vector3& rotation) noexcept;

    /// @brief Creates a 3D rotation Matrix from the given angle for each of the x, y, and z axis.
    static void Rotation(const Vector3& rotation, Matrix* result) noexcept;

    /// @brief	Creates a 3D rotation Matrix from the given rotation Quaternion.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Rotation(const Quaternion& rotation) noexcept;

    /// @brief	Creates a 3D rotation Matrix from the given rotation Quaternion.
    static constexpr void Rotation(const Quaternion& rotation, Matrix* result) noexcept;

    /// @brief Creates a 3D rotation matrix from the given cosine, sine and axis.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param axis The axis around which the rotation occurs.
    ATTRIBUTE_NODISCARD
    static Matrix Rotation(f32 cos, f32 sin, const Vector3& axis) noexcept;

    /// @brief Creates a 3D rotation matrix from the given cosine, sine and axis.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param axis The axis around which the rotation occurs.
    /// @param result The output of the function.
    static void Rotation(f32 cos, f32 sin, const Vector3& axis, Matrix* result) noexcept;

    /// @brief Creates a 3D scaling matrix from the given Vector3.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Scaling(const Vector3& scale) noexcept;

    /// @brief Creates a 3D scaling matrix from the given Vector3.
    static constexpr void Scaling(const Vector3& scale, Matrix* result) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    ATTRIBUTE_NODISCARD
    static Matrix Trs(const Vector3& translation, const Vector3& rotation, const Vector3& scale) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    static void Trs(const Vector3& translation, const Vector3& rotation, const Vector3& scale, Matrix* result) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    ATTRIBUTE_NODISCARD
    static Matrix Trs(const Vector3& translation, f32 rotationAngle, const Vector3& rotationAxis, const Vector3& scale) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    static void Trs(const Vector3& translation, f32 rotationAngle, const Vector3& rotationAxis, const Vector3& scale, Matrix* result) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Trs(const Vector3& translation, const Matrix& rotation, const Vector3& scale) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    static constexpr void Trs(const Vector3& translation, const Matrix& rotation, const Vector3& scale, Matrix* result) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Trs(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept;

    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    static constexpr void Trs(const Vector3& translation, const Quaternion& rotation, const Vector3& scale, Matrix* result) noexcept;

    /// @brief Creates a view Matrix, looking from an @c eye to a @c center using an @c up vector.
    ATTRIBUTE_NODISCARD
    static Matrix LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept;

    /// @brief Creates a view Matrix, looking from an @c eye to a @c center using an @c up vector.
    static void LookAt(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix* result) noexcept;

    /// @brief Creates a perspective projection Matrix from the given @c fov (Field Of View) and aspect ratio.
    ///
    ///	Anything closer than @c near or further than @c far is discarded.
    ATTRIBUTE_NODISCARD
    static Matrix Perspective(f32 fov, f32 aspectRatio, f32 near, f32 far);

    /// @brief Creates a perspective projection Matrix from the given @c fov (Field Of View) and aspect ratio.
    ///
    ///	Anything closer than @c near or further than @c far is discarded.
    static void Perspective(f32 fov, f32 aspectRatio, f32 near, f32 far, Matrix* result);

    /// @brief Creates an orthographic projection Matrix from the given @c left, @c right, @c bottom, and @c top screen positions.
    ///
    ///	Anything closer than @c near or further than @c far is discarded.
    ATTRIBUTE_NODISCARD
    static constexpr Matrix Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

    /// @brief Creates an orthographic projection Matrix from the given @c left, @c right, @c bottom, and @c top screen positions.
    ///
    ///	Anything closer than @c near or further than @c far is discarded.
    static constexpr void Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far, Matrix* result);

    /// @brief Creates a Matrix with all its values set to 0.
    constexpr Matrix() = default;

    /// @brief Creates a Matrix with all its values set to this default value.
    constexpr explicit Matrix(f32 defaultValue) noexcept;

    /// @brief Constructs a Matrix with its components set to the data pointed by @c data.
    ///
    /// This constructor assumes that @c data is a valid pointer pointing to at least 16 @c f32 values.
    ///
    /// @param data The data where the values for this matrix's components are located.
    constexpr explicit Matrix(const f32* data) noexcept;

    /// @brief Constructs a Matrix with 4 column vectors.
    constexpr Matrix(
        const Vector4& c0,
        const Vector4& c1,
        const Vector4& c2,
        const Vector4& c3
    ) noexcept;

    /// @brief Constructs a Matrix with 16 f32 values.
    constexpr Matrix(
        f32 m00, f32 m01, f32 m02, f32 m03,
        f32 m10, f32 m11, f32 m12, f32 m13,
        f32 m20, f32 m21, f32 m22, f32 m23,
        f32 m30, f32 m31, f32 m32, f32 m33
    ) noexcept;

    /// @brief Gets a pointer to the first value of this Matrix.
    ///
    /// @returns A pointer to the first value of this Matrix.
    ATTRIBUTE_NODISCARD
    constexpr const f32* Data() const noexcept;

    /// @brief Gets a pointer to the first value of this Matrix.
    ///
    /// @returns A pointer to the first value of this Matrix.
    ATTRIBUTE_NODISCARD
    constexpr f32* Data() noexcept;

    /// @brief Uses the @c std::cout stream to print the values of this matrix in a square-like shape, e.g. by using newlines to make it easier to read.
    void DebugPrint() const noexcept;

    /// @brief Returns whether the Matrix has everything except its diagonal set to zero.
    ATTRIBUTE_NODISCARD
    constexpr bool IsDiagonal() const noexcept;

    /// @brief Returns whether the Matrix is the identity matrix.
    ///
    /// If this returns true, Matrix::Identity() == *this should be true.
    ATTRIBUTE_NODISCARD
    constexpr bool IsIdentity() const noexcept;

    /// @brief Returns whether this Matrix has everything set to zero.
    ATTRIBUTE_NODISCARD
    constexpr bool IsNull() const noexcept;

    /// @brief Returns whether the Matrix is symmetric by its diagonal elements.
    ATTRIBUTE_NODISCARD
    constexpr bool IsSymmetric() const noexcept;

    /// @brief Returns whether the Matrix is symmetric by its diagonal elements but one of the sides is the opposite of the other.
    ATTRIBUTE_NODISCARD
    constexpr bool IsAntisymmetric() const noexcept;

    /// @brief Returns the diagonal elements of the Matrix.
    ATTRIBUTE_NODISCARD
    constexpr Vector4 Diagonal() const noexcept;

    /// @brief Returns the diagonal elements of the Matrix.
    constexpr void Diagonal(Vector4* result) const noexcept;

    /// @brief Returns the sum of the diagonal elements of the Matrix.
    ATTRIBUTE_NODISCARD
    constexpr f32 Trace() const noexcept;

    /// @brief Returns the determinant of this Matrix.
    ATTRIBUTE_NODISCARD
    constexpr f32 Determinant() const noexcept;

    /// @brief Switches the Matrix by its diagonal elements.
    ATTRIBUTE_NODISCARD
    constexpr Matrix Transposed() const noexcept;

    /// @brief Switches the Matrix by its diagonal elements.
    constexpr void Transposed(Matrix* result) const noexcept;

    /// @brief Computes the invert of this Matrix, e.g. @c *this * Inverted() == Identity() is true.
    ATTRIBUTE_NODISCARD
    constexpr Matrix Inverted() const;

    /// @brief Computes the invert of this Matrix, e.g. @c *this * Inverted() == Identity() is true.
    constexpr void Inverted(Matrix* result) const;

    /// @brief Decomposes this Matrix (assuming this is a model matrix) into its components.
    ///
    /// This is a heavy operation, try to avoid using this each frame.
    ///
    /// @param translation Translation result
    /// @param orientation Rotation result
    /// @param scale Scaling result
    /// @param skew Skew result
    /// @param perspective Perspective result
    /// @return @c false if the operation failed
    bool Decompose(Vector3* translation, Quaternion* orientation, Vector3* scale, Vector3* skew, Vector4* perspective) const;

    /// @brief Retrieves this matrix's value at position @c [col, row].
    ///
    /// @param row The index of the col to get.
    /// @param col The index of the column to get.
    /// @returns The value at position @c [col, row].
    ATTRIBUTE_NODISCARD
    constexpr f32 At(size_t row, size_t col) const;

    /// @brief Retrieves this matrix's col at position @c [col, row].
    ///
    /// @param row The index of the col to get.
    /// @param col The index of the column to get.
    /// @returns The value at position @c [col, row].
    ATTRIBUTE_NODISCARD
    constexpr f32& At(size_t row, size_t col);

    /// @brief Retrieves this matrix's column vector at position @c col.
    ///
    ///	If you want to get a value of this matrix, consider using <see cref="At(size_t, size_t)"/>
    ///	instead, as it is optimized for direct-value access.
    ///
    /// @param col The index of the column to get.
    /// @returns The column vector at index @c col.
    ATTRIBUTE_NODISCARD
    constexpr Vector4 operator[](size_t col) const;

    /// @brief Retrieves this matrix's column vector at position @c col.
    ///
    ///	If you want to get a value of this matrix, consider using <see cref="At(size_t, size_t)"/>
    ///	instead, as it is optimized for direct-value access.
    ///
    /// @param col The index of the column to get.
    /// @returns The column vector at index @c col.
    ATTRIBUTE_NODISCARD
    constexpr Vector4& operator[](size_t col);

    /// @brief Converts this Matrix to a Matrix3 by cropping its last row and column.
    ATTRIBUTE_NODISCARD
    constexpr explicit operator Matrix3() const;
};

static_assert(std::is_default_constructible_v<Matrix>, "Class Matrix must be default constructible.");
static_assert(std::is_copy_constructible_v<Matrix>, "Class Matrix must be copy constructible.");
static_assert(std::is_move_constructible_v<Matrix>, "Class Matrix must be move constructible.");
static_assert(std::is_copy_assignable_v<Matrix>, "Class Matrix must be copy assignable.");
static_assert(std::is_move_assignable_v<Matrix>, "Class Matrix must be move assignable.");

constexpr Matrix::Matrix(const f32 defaultValue) noexcept
    : m00(defaultValue), m10(defaultValue), m20(defaultValue), m30(defaultValue)
    , m01(defaultValue), m11(defaultValue), m21(defaultValue), m31(defaultValue)
    , m02(defaultValue), m12(defaultValue), m22(defaultValue), m32(defaultValue)
    , m03(defaultValue), m13(defaultValue), m23(defaultValue), m33(defaultValue)
{
}

constexpr Matrix::Matrix(const f32* const data) noexcept
    : m00(data[0]), m10(data[1]), m20(data[2]), m30(data[3])
    , m01(data[4]), m11(data[5]), m21(data[6]), m31(data[7])
    , m02(data[8]), m12(data[9]), m22(data[10]), m32(data[11])
    , m03(data[12]), m13(data[13]), m23(data[14]), m33(data[15])
{
}

constexpr Matrix::Matrix(const Vector4& c0, const Vector4& c1, const Vector4& c2, const Vector4& c3) noexcept
    : m00(c0.x), m10(c1.x), m20(c2.x), m30(c3.x)
    , m01(c0.y), m11(c1.y), m21(c2.y), m31(c3.y)
    , m02(c0.z), m12(c1.z), m22(c2.z), m32(c3.z)
    , m03(c0.w), m13(c1.w), m23(c2.w), m33(c3.w)
{
}

constexpr Matrix::Matrix(
    const f32 m00, const f32 m01, const f32 m02, const f32 m03,
    const f32 m10, const f32 m11, const f32 m12, const f32 m13,
    const f32 m20, const f32 m21, const f32 m22, const f32 m23,
    const f32 m30, const f32 m31, const f32 m32, const f32 m33
) noexcept
    : m00(m00), m10(m10), m20(m20), m30(m30)
    , m01(m01), m11(m11), m21(m21), m31(m31)
    , m02(m02), m12(m12), m22(m22), m32(m32)
    , m03(m03), m13(m13), m23(m23), m33(m33)
{
}

constexpr Matrix::operator Matrix3() const
{
    return Matrix3(
        m00, m01, m02,
        m10, m11, m12,
        m20, m21, m22
    );
}

/// @brief Returns the opposite of a Matrix.
///
/// This effectively means replacing all values of this Matrix with their opposite.
ATTRIBUTE_NODISCARD
constexpr Matrix operator-(const Matrix& matrix) noexcept
{
    return Matrix(
        -matrix.m00, -matrix.m01, -matrix.m02, -matrix.m03,
        -matrix.m10, -matrix.m11, -matrix.m12, -matrix.m13,
        -matrix.m20, -matrix.m21, -matrix.m22, -matrix.m23,
        -matrix.m30, -matrix.m31, -matrix.m32, -matrix.m33
    );
}

/// @brief Adds the values of two @ref Matrix "Matrices" one by one.
ATTRIBUTE_NODISCARD
constexpr Matrix operator+(const Matrix& m1, const Matrix& m2) noexcept
{
    return Matrix(
        m1.m00 + m2.m00, m1.m01 + m2.m01, m1.m02 + m2.m02, m1.m03 + m2.m03,
        m1.m10 + m2.m10, m1.m11 + m2.m11, m1.m12 + m2.m12, m1.m13 + m2.m13,
        m1.m20 + m2.m20, m1.m21 + m2.m21, m1.m22 + m2.m22, m1.m23 + m2.m23,
        m1.m30 + m2.m30, m1.m31 + m2.m31, m1.m32 + m2.m32, m1.m33 + m2.m33
    );
}

/// @brief Subtracts the values of two @ref Matrix "Matrices" one by one.
ATTRIBUTE_NODISCARD
constexpr Matrix operator-(const Matrix& m1, const Matrix& m2) noexcept { return m1 + -m2; }

/// @brief Multiplies all values of a Matrix by a @p scalar.
ATTRIBUTE_NODISCARD
constexpr Matrix operator*(const Matrix& m, const f32 scalar) noexcept
{
    return Matrix(
        m.m00 * scalar, m.m01 * scalar, m.m02 * scalar, m.m03 * scalar,
        m.m10 * scalar, m.m11 * scalar, m.m12 * scalar, m.m13 * scalar,
        m.m20 * scalar, m.m21 * scalar, m.m22 * scalar, m.m23 * scalar,
        m.m30 * scalar, m.m31 * scalar, m.m32 * scalar, m.m33 * scalar
    );
}

/// @brief Multiplies all values of a Matrix by a @p scalar.
ATTRIBUTE_NODISCARD
constexpr Matrix operator*(const f32 factor, const Matrix& m) noexcept { return m * factor; }

/// @brief Multiplies a Vector2 by a Matrix.
ATTRIBUTE_NODISCARD
constexpr Vector2 operator*(const Matrix& m, Vector2 v) noexcept
{
    return Vector2(
        v.x * m.m00 + v.y * m.m01 + m.m02 + m.m03,
        v.x * m.m10 + v.y * m.m11 + m.m12 + m.m13
    );
}

/// @brief Multiplies a Vector3 by a Matrix.
ATTRIBUTE_NODISCARD
constexpr Vector3 operator*(const Matrix& m, const Vector3& v) noexcept
{
    return Vector3(
        v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + m.m03,
        v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + m.m13,
        v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + m.m23
    );
}

/// @brief Multiplies a Vector4 by a Matrix.
ATTRIBUTE_NODISCARD
constexpr Vector4 operator*(const Matrix& m, const Vector4& v) noexcept
{
    return Vector4(
        v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + m.m03,
        v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + m.m13,
        v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + m.m23,
        v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + m.m33
    );
}

/// @brief Multiplies two @ref Matrix "Matrices".
ATTRIBUTE_NODISCARD
constexpr Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept
{
    return Matrix(
        m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20 + m1.m03 * m2.m30,
        m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21 + m1.m03 * m2.m31,
        m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22 + m1.m03 * m2.m32,
        m1.m00 * m2.m03 + m1.m01 * m2.m13 + m1.m02 * m2.m23 + m1.m03 * m2.m33,

        m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20 + m1.m13 * m2.m30,
        m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31,
        m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32,
        m1.m10 * m2.m03 + m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33,

        m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20 + m1.m23 * m2.m30,
        m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31,
        m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32,
        m1.m20 * m2.m03 + m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33,

        m1.m30 * m2.m00 + m1.m31 * m2.m10 + m1.m32 * m2.m20 + m1.m33 * m2.m30,
        m1.m30 * m2.m01 + m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31,
        m1.m30 * m2.m02 + m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32,
        m1.m30 * m2.m03 + m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33
    );
}

/// @brief Adds two @ref Matrix "Matrices" according to @ref operator+(const Matrix&, const Matrix&), placing the result in @p m1.
constexpr Matrix& operator+=(Matrix& m1, const Matrix& m2) noexcept { return m1 = m1 + m2; }

/// @brief Subtracts two @ref Matrix "Matrices" according to @ref operator-(const Matrix&, const Matrix&), placing the result in @p m1.
constexpr Matrix& operator-=(Matrix& m1, const Matrix& m2) noexcept { return m1 = m1 - m2; }

/// @brief Multiplies a Matrix by a @p scalar according to @ref operator*(const Matrix&, const f32), placing the result in @p m.
constexpr Matrix& operator*=(Matrix& m, const f32 scalar) noexcept { return m = m * scalar; }

/// @brief Multiplies two @ref Matrix "Matrices" according to @ref operator*(const Matrix&, const Matrix&), placing the result in @p m1.
constexpr Matrix& operator*=(Matrix& m1, const Matrix& m2) noexcept { return m1 = m1 * m2; }

/// @brief	Checks if two Matrices are equal.
ATTRIBUTE_NODISCARD
constexpr bool operator==(const Matrix& a, const Matrix& b)
{
    return a.m00 == b.m00 && a.m01 == b.m01 && a.m02 == b.m02 && a.m03 == b.m03
        && a.m10 == b.m10 && a.m11 == b.m11 && a.m12 == b.m12 && a.m13 == b.m13
        && a.m20 == b.m20 && a.m21 == b.m21 && a.m22 == b.m22 && a.m23 == b.m23
        && a.m30 == b.m30 && a.m31 == b.m31 && a.m32 == b.m32 && a.m33 == b.m33;
}

/// @brief	Checks if two Matrices are different.
ATTRIBUTE_NODISCARD
constexpr bool operator!=(const Matrix& a, const Matrix& b) { return !(a == b); }

constexpr Matrix Matrix::Identity() noexcept
{
    return Matrix(
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr void Matrix::Identity(Matrix* result) noexcept
{
    *result = Matrix(
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr Matrix Matrix::Translation(const Vector3 &translation) noexcept
{
    return Matrix(
        1.f, 0.f, 0.f, translation.x,
        0.f, 1.f, 0.f, translation.y,
        0.f, 0.f, 1.f, translation.z,
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr void Matrix::Translation(const Vector3& translation, Matrix* result) noexcept
{
    *result = Matrix(
        1.f, 0.f, 0.f, translation.x,
        0.f, 1.f, 0.f, translation.y,
        0.f, 0.f, 1.f, translation.z,
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr Matrix Matrix::RotationX(const f32 cos, const f32 sin) noexcept
{
    return Matrix(
        1.f,    0.f,    0.f,    0.f,
        0.f,    cos,   -sin,    0.f,
        0.f,    sin,    cos,    0.f,
        0.f,    0.f,    0.f,    1.f
    );
}

constexpr void Matrix::RotationX(const f32 cos, const f32 sin, Matrix* result) noexcept
{
    *result = Matrix(
        1.f,    0.f,    0.f,    0.f,
        0.f,    cos,   -sin,    0.f,
        0.f,    sin,    cos,    0.f,
        0.f,    0.f,    0.f,    1.f
    );
}

constexpr Matrix Matrix::RotationY(const f32 cos, const f32 sin) noexcept
{
    return Matrix(
         cos,    0.f,    sin,    0.f,
         0.f,    1.f,    0.f,    0.f,
        -sin,    0.f,    cos,    0.f,
         0.f,    0.f,    0.f,    1.f
    );
}

constexpr void Matrix::RotationY(const f32 cos, const f32 sin, Matrix* result) noexcept
{
    *result = Matrix(
         cos,    0.f,    sin,    0.f,
         0.f,    1.f,    0.f,    0.f,
        -sin,    0.f,    cos,    0.f,
         0.f,    0.f,    0.f,    1.f
    );
}

constexpr Matrix Matrix::RotationZ(const f32 cos, const f32 sin) noexcept
{
    return Matrix(
        cos,   -sin,    0.f,    0.f,
        sin,    cos,    0.f,    0.f,
        0.f,    0.f,    1.f,    0.f,
        0.f,    0.f,    0.f,    1.f
    );
}

constexpr void Matrix::RotationZ(const f32 cos, const f32 sin, Matrix* result) noexcept
{
    *result = Matrix(
        cos,   -sin,    0.f,    0.f,
        sin,    cos,    0.f,    0.f,
        0.f,    0.f,    1.f,    0.f,
        0.f,    0.f,    0.f,    1.f
    );
}

constexpr Matrix Matrix::Rotation(const Quaternion& rotation) noexcept
{
    Matrix result;
    Rotation(rotation, &result);
    return result;
}

constexpr void Matrix::Rotation(const Quaternion& rotation, Matrix* result) noexcept
{
    const f32 xx = SQ(rotation.X());
    const f32 yy = SQ(rotation.Y());
    const f32 zz = SQ(rotation.Z());

    const f32 xy = rotation.X() * rotation.Y();
    const f32 wz = rotation.Z() * rotation.W();
    const f32 xz = rotation.Z() * rotation.X();
    const f32 wy = rotation.Y() * rotation.W();
    const f32 yz = rotation.Y() * rotation.Z();
    const f32 wx = rotation.X() * rotation.W();

    *result = Matrix(
        1.f - 2.f * (yy + zz), 2.f * (xy - wz), 2.f * (xz + wy), 0.f,
        2.f * (xy + wz), 1.f - 2.f * (zz + xx), 2.f * (yz - wx), 0.f,
        2.f * (xz - wy), 2.f * (yz + wx), 1.f - 2.f * (yy + xx), 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr Matrix Matrix::Scaling(const Vector3 &scale) noexcept
{
    return Matrix(
        scale.x,       0.f,     0.f, 0.f,
              0.f, scale.y,     0.f, 0.f,
              0.f,     0.f, scale.z, 0.f,
              0.f,     0.f,     0.f, 1.f
    );
}

constexpr void Matrix::Scaling(const Vector3& scale, Matrix* result) noexcept
{
    *result = Matrix(
        scale.x,       0.f,     0.f, 0.f,
              0.f, scale.y,     0.f, 0.f,
              0.f,     0.f, scale.z, 0.f,
              0.f,     0.f,     0.f, 1.f
    );
}

constexpr Matrix Matrix::Trs(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept { return Trs(translation, Rotation(rotation), scale); }

constexpr void Matrix::Trs(const Vector3& translation, const Quaternion& rotation, const Vector3& scale, Matrix* result) noexcept { Trs(translation, Rotation(rotation), scale, result); }

constexpr Matrix Matrix::Orthographic(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 near, const f32 far)
{
    if (near > far) ATTRIBUTE_UNLIKELY
        throw std::invalid_argument("Near must be smaller than far.");

    return Matrix(
        2.f / (right - left), 0.f, 0.f, -((right + left) / (right - left)),
        0.f, 2.f / (top - bottom), 0.f, -((top + bottom) / (top - bottom)),
        0.f, 0.f, -2.f / (far - near), -((far + near) / (far - near)),
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr void Matrix::Orthographic(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 near, const f32 far, Matrix* result)
{
    if (near > far) ATTRIBUTE_UNLIKELY
        throw std::invalid_argument("Near must be smaller than far.");

    *result = Matrix(
        2.f / (right - left), 0.f, 0.f, -((right + left) / (right - left)),
        0.f, 2.f / (top - bottom), 0.f, -((top + bottom) / (top - bottom)),
        0.f, 0.f, -2.f / (far - near), -((far + near) / (far - near)),
        0.f, 0.f, 0.f, 1.f
    );
}

constexpr const f32* Matrix::Data() const noexcept { return &m00; }

constexpr f32* Matrix::Data() noexcept { return &m00; }

constexpr bool Matrix::IsDiagonal() const noexcept
{
    return                      Calc::IsZero(m01) && Calc::IsZero(m02) && Calc::IsZero(m03)
        && Calc::IsZero(m10)                      && Calc::IsZero(m12) && Calc::IsZero(m13)
        && Calc::IsZero(m20) && Calc::IsZero(m21)                      && Calc::IsZero(m23)
        && Calc::IsZero(m30) && Calc::IsZero(m31) && Calc::IsZero(m32);
}

constexpr bool Matrix::IsIdentity() const noexcept
{
    if (!IsDiagonal())
        return false;

    return Calc::Equals(m00, 1.f) && Calc::Equals(m11, 1.f) && Calc::Equals(m22, 1.f) && Calc::Equals(m33, 1.f);
}

constexpr bool Matrix::IsNull() const noexcept
{
    if (!IsDiagonal())
        return false;

    return Calc::IsZero(m00) && Calc::IsZero(m11) && Calc::IsZero(m22) && Calc::IsZero(m33);
}

constexpr bool Matrix::IsSymmetric() const noexcept
{
    return Calc::Equals(m01, m10) && Calc::Equals(m02, m20) && Calc::Equals(m03, m30)
        && Calc::Equals(m12, m21) && Calc::Equals(m13, m31)
        && Calc::Equals(m23, m32);
}

constexpr bool Matrix::IsAntisymmetric() const noexcept
{
    return Calc::Equals(m01, -m10) && Calc::Equals(m02, -m20) && Calc::Equals(m03, -m30)
        && Calc::Equals(m12, -m21) && Calc::Equals(m13, -m31)
        && Calc::Equals(m23, -m32);
}

constexpr Vector4 Matrix::Diagonal() const noexcept { return Vector4(m00, m11, m22, m33); }

constexpr void Matrix::Diagonal(Vector4* result) const noexcept { *result = Vector4(m00, m11, m22, m33); }

constexpr f32 Matrix::Trace() const noexcept { return m00 + m11 + m22 + m33; }

constexpr f32 Matrix::Determinant() const noexcept
{
    // Definition from MonoGame/XNA: https://github.com/MonoGame/MonoGame/blob/b30122c99597eaf81b81f32ab1d467a7b4185c73/MonoGame.Framework/Matrix.cs

    const f32 det2233 = m22 * m33 - m32 * m23;
    const f32 det1233 = m12 * m33 - m32 * m13;
    const f32 det1223 = m12 * m23 - m22 * m13;
    const f32 det0233 = m02 * m33 - m32 * m03;
    const f32 det0223 = m02 * m23 - m22 * m03;
    const f32 det0213 = m02 * m13 - m12 * m03;

    return m00 * (m11 * det2233 - m21 * det1233 + m31 * det1223)
        - m10 * (m01 * det2233 - m21 * det0233 + m31 * det0223)
        + m20 * (m01 * det1233 - m11 * det0233 + m31 * det0213)
        - m30 * (m01 * det1223 - m11 * det0223 + m21 * det0213);
}

constexpr Matrix Matrix::Transposed() const noexcept
{
    return Matrix(
        m00, m10, m20, m30,
        m01, m11, m21, m31,
        m02, m12, m22, m32,
        m03, m13, m23, m33
    );
}

constexpr void Matrix::Transposed(Matrix* result) const noexcept
{
    *result = Matrix(
        m00, m10, m20, m30,
        m01, m11, m21, m31,
        m02, m12, m22, m32,
        m03, m13, m23, m33
    );
}

constexpr Matrix Matrix::Inverted() const
{
    Matrix result;
    Inverted(&result);
    return result;
}

constexpr void Matrix::Inverted(Matrix* result) const
{
    if (Determinant() == 0.f) ATTRIBUTE_UNLIKELY
        throw std::invalid_argument("Matrix isn't invertible");

    // Definition from MonoGame/XNA: https://github.com/MonoGame/MonoGame/blob/b30122c99597eaf81b81f32ab1d467a7b4185c73/MonoGame.Framework/Matrix.cs

    const f32 val17 = m22 * m33 - m23 * m32;
    const f32 val18 = m21 * m33 - m23 * m31;
    const f32 val19 = m21 * m32 - m22 * m31;
    const f32 val20 = m20 * m33 - m23 * m30;
    const f32 val21 = m20 * m32 - m22 * m30;
    const f32 val22 = m20 * m31 - m21 * m30;
    const f32 val23 = m11 * val17 - m12 * val18 + m13 * val19;
    const f32 val24 = -(m10 * val17 - m12 * val20 + m13 * val21);
    const f32 val25 = m10 * val18 - m11 * val20 + m13 * val22;
    const f32 val26 = -(m10 * val19 - m11 * val21 + m12 * val22);
    const f32 val27 = 1.f / (m00 * val23 + m01 * val24 + m02 * val25 + m03 * val26);

    const f32 val28 = m12 * m33 - m13 * m32;
    const f32 val29 = m11 * m33 - m13 * m31;
    const f32 val30 = m11 * m32 - m12 * m31;
    const f32 val31 = m10 * m33 - m13 * m30;
    const f32 val32 = m10 * m32 - m12 * m30;
    const f32 val33 = m10 * m31 - m11 * m30;

    const f32 val34 = m12 * m23 - m13 * m22;
    const f32 val35 = m11 * m23 - m13 * m21;
    const f32 val36 = m11 * m22 - m12 * m21;
    const f32 val37 = m10 * m23 - m13 * m20;
    const f32 val38 = m10 * m22 - m12 * m20;
    const f32 val39 = m10 * m21 - m11 * m20;

    *result = Matrix(
        val23 * val27,
        -(m01 * val17 - m02 * val18 + m03 * val19) * val27,
        (m01 * val28 - m02 * val29 + m03 * val30) * val27,
        -(m01 * val34 - m02 * val35 + m03 * val36) * val27,

        val24 * val27,
        (m00 * val17 - m02 * val20 + m03 * val21) * val27,
        -(m00 * val28 - m02 * val31 + m03 * val32) * val27,
        (m00 * val34 - m02 * val37 + m03 * val38) * val27,

        val25 * val27,
        -(m00 * val18 - m01 * val20 + m03 * val22) * val27,
        (m00 * val29 - m01 * val31 + m03 * val33) * val27,
        -(m00 * val35 - m01 * val37 + m03 * val39) * val27,

        val26 * val27,
        (m00 * val19 - m01 * val21 + m02 * val22) * val27,
        -(m00 * val30 - m01 * val32 + m02 * val33) * val27,
        (m00 * val36 - m01 * val38 + m02 * val39) * val27
    );
}

constexpr f32 Matrix::At(const size_t row, const size_t col) const
{
    if (row < 4 && col < 4) ATTRIBUTE_LIKELY
        return Data()[row * 4 + col];

    ATTRIBUTE_UNLIKELY
    throw std::out_of_range("Matrix subscript out of range");
}

constexpr f32& Matrix::At(const size_t row, const size_t col)
{
    if (row < 4 && col < 4) ATTRIBUTE_LIKELY
        return Data()[row * 4 + col];

    ATTRIBUTE_UNLIKELY
    throw std::out_of_range("Matrix subscript out of range");
}

constexpr Vector4 Matrix::operator[](const size_t col) const
{
    return Vector4(Data() + static_cast<ptrdiff_t>(col) * 4);
}

constexpr Vector4& Matrix::operator[](const size_t col)
{
    // Pointer arithmetic magic to get around not being able to use reinterpret_cast
    return *static_cast<Vector4*>(static_cast<void*>(Data() + static_cast<ptrdiff_t>(col) * 4));
}

/// @brief Streams a Matrix into @p out, printing its values one by one on a single line.
///
/// If you instead want a multiline print, you can use Matrix::DebugPrint.
MOUNTAIN_API std::ostream& operator<<(std::ostream& out, const Matrix& m);

constexpr Matrix Matrix::Trs(const Vector3& translation, const Matrix& rotation, const Vector3& scale) noexcept
{
    const Matrix result = Matrix(
        1.f, 0.f, 0.f, translation.x,
        0.f, 1.f, 0.f, translation.y,
        0.f, 0.f, 1.f, translation.z,
        0.f, 0.f, 0.f, 1.f
    );

    Matrix temp;
    Scaling(scale, &temp);

    return result * rotation * temp;
}

constexpr void Matrix::Trs(const Vector3& translation, const Matrix& rotation, const Vector3& scale, Matrix* result) noexcept
{
    *result = Matrix(
        1.f, 0.f, 0.f, translation.x,
        0.f, 1.f, 0.f, translation.y,
        0.f, 0.f, 1.f, translation.z,
        0.f, 0.f, 0.f, 1.f
    );

    Matrix temp;
    Scaling(scale, &temp);

    *result = *result * rotation * temp;
}

template <>
struct std::formatter<Matrix>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Matrix m, FmtContext& ctx) const;

private:
    std::string m_Format;
    bool m_Multiline = false;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Matrix, c8>::parse(ParseContext& ctx)
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
typename FmtContext::iterator std::formatter<Matrix>::format(Matrix m, FmtContext &ctx) const
{
    std::ostringstream out;

    const c8 separator = m_Multiline ? '\n' : ' ';

    out << std::vformat(
            "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]" + separator
            + "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]" + separator
            + "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]" + separator
            + "[ {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ; {:" + m_Format + "} ]",
            std::make_format_args(
                    m.m00, m.m01, m.m02, m.m03,
                    m.m10, m.m11, m.m12, m.m13,
                    m.m20, m.m21, m.m22, m.m23,
                    m.m30, m.m31, m.m32, m.m33
            )
    );

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
