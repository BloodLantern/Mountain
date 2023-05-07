#pragma once

#include <compare>
#include <ostream>

#include "vector3.hpp"

class Vector;
class Matrix;
class Matrix4x4;

/// @brief The Matrix3x3 class represents a two-dimensional array mainly used for mathematical operations.
class Matrix3x3
{
public:
    /// @brief Returns the identity matrix.
    ///        The identity matrix is a matrix with its diagonal
    ///        set to one and everything else set to zero.
    static Matrix3x3 Identity();

    /// @brief Creates a matrix with all its values set to this default value.
    constexpr Matrix3x3(const float defaultValue = 0.f)
        : r0(defaultValue), r1(defaultValue), r2(defaultValue) {}
    constexpr Matrix3x3(const Vector3& r0, const Vector3& r1, const Vector3& r2)
        : r0(r0), r1(r1), r2(r2) {}
    constexpr Matrix3x3(
        const float r00, const float r01, const float r02,
        const float r10, const float r11, const float r12,
        const float r20, const float r21, const float r22
    )
        : r0(r00, r01, r02),
          r1(r10, r11, r12),
          r2(r20, r21, r22)
    {}
    /// @brief Copies the content of the given matrix to this one.
    constexpr Matrix3x3(const Matrix3x3& matrix)
        : r0(matrix.r0), r1(matrix.r1), r2(matrix.r2) {}

    /// @brief Returns whether the matrix has everything except its diagonal set to zero.
    [[nodiscard]]
    bool IsDiagonal() const;
    /// @brief Returns whether the matrix is the identity matrix.
    ///        If this returns true, Matrix3x3::Identity() == *this should be true.
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
    Vector3 Diagonal() const;
    /// @brief Returns the sum of the diagonal elements of the matrix.
    [[nodiscard]]
    float Trace() const;
    /// @brief Returns a matrix with its data set to the given indices of this one.
    [[nodiscard]]
    Matrix3x3 SubMatrix(const size_t rowIndex, const size_t colIndex, const size_t rows, const size_t cols) const;
    /// @brief Returns the determinant of this matrix.
    [[nodiscard]]
    float Determinant() const;
    /// @brief Sets this matrix to the identity matrix.
    Matrix3x3& LoadIdentity(this Matrix3x3& self);
    /// @brief Switches the matrix by its diagonal elements.
    Matrix3x3& Transpose(this Matrix3x3& self);
    /// @brief Adds the given matrix to the right of this one.
    Matrix Augmented(this Matrix3x3& self, const Matrix3x3& other);
    Matrix3x3& Inverse(this Matrix3x3& self);

    /// @brief Switches the given matrix by its diagonal elements.
    [[nodiscard]]
    static Matrix3x3 Transpose(const Matrix3x3& matrix);
    /// @brief Adds the 'm2' to the right of 'm1'.
    [[nodiscard]]
    static Matrix Augmented(const Matrix3x3& m1, const Matrix3x3& m2);
    /// @brief Computes the inverse of the given matrix using the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix3x3 Inverse(const Matrix3x3& matrix);

    [[nodiscard]]
    constexpr const Vector3& operator[](const size_t row) const;
    [[nodiscard]]
    constexpr Vector3& operator[](const size_t row);
    explicit operator Vector2() const;
    explicit operator Vector3() const;
    explicit operator Vector() const;
    operator Matrix4x4() const;
    operator Matrix() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Matrix3x3& a, const Matrix3x3& b) = default;

private:
    Vector3 r0, r1, r2;
};

[[nodiscard]]
Matrix3x3 operator-(const Matrix3x3& matrix);
[[nodiscard]]
Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2);
[[nodiscard]]
Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2);
[[nodiscard]]
Matrix3x3 operator*(const Matrix3x3& m, const float scalar);
[[nodiscard]]
Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);

Matrix3x3& operator+=(Matrix3x3& m1, const Matrix3x3& m2);
Matrix3x3& operator-=(Matrix3x3& m1, const Matrix3x3& m2);
Matrix3x3& operator*=(Matrix3x3& m, const float scalar);
Matrix3x3& operator*=(Matrix3x3& m1, const Matrix3x3& m2);

std::ostream& operator<<(std::ostream& out, const Matrix3x3& m);
