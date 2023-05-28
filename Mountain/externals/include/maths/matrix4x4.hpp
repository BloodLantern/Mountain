#pragma once

#include "vector4.hpp"

#include <compare>
#include <ostream>

class Vector2;
class Vector3;

/// @brief The Matrix4x4 class represents a two-dimensional array mainly used for mathematical operations.
class Matrix4x4
{
public:
    /// @brief Returns the identity matrix.
    ///        The identity matrix is a matrix with its diagonal
    ///        set to one and everything else set to zero.
    static Matrix4x4 Identity();

    /// @brief Creates a matrix with all its values set to this default value.
    constexpr Matrix4x4(const float defaultValue = 0.f)
        : r0(defaultValue), r1(defaultValue), r2(defaultValue), r3(defaultValue) {}
    constexpr Matrix4x4(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3)
        : r0(r0), r1(r1), r2(r2), r3(r3) {}
    constexpr Matrix4x4(
        const float r00, const float r01, const float r02, const float r03,
        const float r10, const float r11, const float r12, const float r13,
        const float r20, const float r21, const float r22, const float r23,
        const float r30, const float r31, const float r32, const float r33
    )
        : r0(r00, r01, r02, r03),
          r1(r10, r11, r12, r13),
          r2(r20, r21, r22, r23),
          r3(r30, r31, r32, r33)
    {}
    /// @brief Copies the content of the given matrix to this one.
    constexpr Matrix4x4(const Matrix4x4& matrix)
        : r0(matrix[0]), r1(matrix[1]), r2(matrix[2]), r3(matrix[3]) {}

    /// @brief Returns whether the matrix has everything except its diagonal set to zero.
    [[nodiscard]]
    bool IsDiagonal() const;
    /// @brief Returns whether the matrix is the identity matrix.
    ///        If this returns true, Matrix4x4::Identity() == *this should be true.
    [[nodiscard]]
    bool IsIdentity() const;
    /// @brief Returns wether this matrix has everything set to zero.
    [[nodiscard]]
    bool IsNull() const;
    /// @brief Returns whether the matrix is symmetric by its diagonal elements.
    [[nodiscard]]
    bool IsSymmetric() const;
    /// @brief Returns whether the matrix is symmetric by its diagonal elements
    ///        but one of the sides is the opposite of the other.
    [[nodiscard]]
    bool IsAntisymmetric() const;
    /// @brief Returns the diagonal elements of the matrix.
    [[nodiscard]]
    Vector4 Diagonal() const;
    /// @brief Returns the sum of the diagonal elements of the matrix.
    [[nodiscard]]
    float Trace() const;
    /// @brief Returns a matrix with its data set to the given indices of this one.
    [[nodiscard]]
    Matrix4x4 SubMatrix(const size_t rowIndex, const size_t colIndex, const size_t rows, const size_t cols) const;
    /// @brief Returns the determinant of this matrix.
    [[nodiscard]]
    float Determinant() const;
    /// @brief Sets this matrix to the identity matrix.
    Matrix4x4& LoadIdentity();
    /// @brief Switches the matrix by its diagonal elements.
    Matrix4x4& Transpose();
    Matrix4x4& GaussJordan();
    Matrix4x4& Inverse();

    /// @brief Switches the given matrix by its diagonal elements.
    [[nodiscard]]
    static Matrix4x4 Transpose(const Matrix4x4& matrix);
    /// @brief Computes the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix4x4 GaussJordan(const Matrix4x4& matrix);
    /// @brief Computes the inverse of the given matrix using the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix4x4 Inverse(const Matrix4x4& matrix);
    /// @brief Creates a 3D translation matrix from the given angle for each of the x, y, and z axis.
    [[nodiscard]]
    static Matrix4x4 Translation2D(const Vector2& translation);
    /// @brief Creates a 3D translation matrix from the given angle for each of the x, y, and z axis.
    [[nodiscard]]
    static Matrix4x4 Translation3D(const Vector3& translation);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    [[nodiscard]]
    static Matrix4x4 TRS(const Vector3& translation, const Vector3& rotation, const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
	/// @param rotationAngle The angle in radians.
    [[nodiscard]]
    static Matrix4x4 TRS(const Vector3& translation, const float rotationAngle, const Vector3& axis, const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    [[nodiscard]]
    static Matrix4x4 TRS(const Vector3& translation, const Matrix4x4& rotation, const Vector3& scale);
    static void ViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix4x4& result);
    static void PerspectiveProjectionMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far, Matrix4x4& result);
    static void OrthographicProjectionMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far, Matrix4x4& result);

    [[nodiscard]]
    constexpr const Vector4& operator[](const size_t row) const;
    [[nodiscard]]
    constexpr Vector4& operator[](const size_t row);
    explicit operator Vector2() const;
    explicit operator Vector3() const;
    explicit operator Vector4() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Matrix4x4& a, const Matrix4x4& b) = default;

private:
    Vector4 r0, r1, r2, r3;
};

[[nodiscard]]
Matrix4x4 operator-(const Matrix4x4& matrix);
[[nodiscard]]
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
[[nodiscard]]
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
[[nodiscard]]
Matrix4x4 operator*(const Matrix4x4& m, const float scalar);
[[nodiscard]]
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4& operator+=(Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4& operator-=(Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4& operator*=(Matrix4x4& m, const float scalar);
Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);

std::ostream& operator<<(std::ostream& out, const Matrix4x4& m);
