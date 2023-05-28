#pragma once

#include <compare>
#include <ostream>

#include "vector2.hpp"

class Matrix3x3;
class Matrix4x4;

/// @brief The Matrix2x2 class represents a two-dimensional array mainly used for mathematical operations.
class Matrix2x2
{
public:
    /// @brief Returns the identity matrix.
    ///        The identity matrix is a matrix with its diagonal
    ///        set to one and everything else set to zero.
    static Matrix2x2 Identity();

    /// @brief Creates a matrix with all its values set to this default value.
    constexpr Matrix2x2(const float defaultValue = 0.f)
        : r0(defaultValue), r1(defaultValue) {}
    constexpr Matrix2x2(const Vector2& r0, const Vector2& r1)
        : r0(r0), r1(r1)
    {}
    constexpr Matrix2x2(
        const float r00, const float r01,
        const float r10, const float r11
    )
        : r0(r00, r01),
          r1(r10, r11)
    {}
    /// @brief Copies the content of the given matrix to this one.
    constexpr Matrix2x2(const Matrix2x2& matrix)
        : r0(matrix.r0), r1(matrix.r1) {}

    /// @brief Returns whether the matrix has everything except its diagonal set to zero.
    [[nodiscard]]
    bool IsDiagonal() const;
    /// @brief Returns whether the matrix is the identity matrix.
    ///        If this returns true, Matrix2x2::Identity() == *this should be true.
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
    Vector2 Diagonal() const;
    /// @brief Returns the sum of the diagonal elements of the matrix.
    [[nodiscard]]
    float Trace() const;
    /// @brief Returns a matrix with its data set to the given indices of this one.
    [[nodiscard]]
    Matrix2x2 SubMatrix(const size_t rowIndex, const size_t colIndex, const size_t rows, const size_t cols) const;
    /// @brief Returns the determinant of this matrix.
    [[nodiscard]]
    float Determinant() const;
    /// @brief Sets this matrix to the identity matrix.
    Matrix2x2& LoadIdentity();
    /// @brief Switches the matrix by its diagonal elements.
    Matrix2x2& Transpose();
    Matrix2x2& Inverse();

    /// @brief Switches the given matrix by its diagonal elements.
    [[nodiscard]]
    static Matrix2x2 Transpose(const Matrix2x2& matrix);
    /// @brief Computes the inverse of the given matrix using the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix2x2 Inverse(const Matrix2x2& matrix);
    /// @brief Creates a 2D scaling matrix from the given Vector2.
    [[nodiscard]]
    static Matrix2x2 Scaling2D(const Vector2 scale);
    /// @brief Creates a 2D rotation matrix from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix2x2 Rotation2D(const float angle);
    /// @brief Creates a 3D rotation matrix around the X axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix2x2 Rotation2D(const float cos, const float sin);

    [[nodiscard]]
    constexpr const Vector2& operator[](const size_t row) const;
    [[nodiscard]]
    constexpr Vector2& operator[](const size_t row);
    explicit operator Vector2() const;
    explicit operator Matrix3x3() const;
    explicit operator Matrix4x4() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Matrix2x2& a, const Matrix2x2& b) = default;

private:
    Vector2 r0, r1;
};

[[nodiscard]]
Matrix2x2 operator-(const Matrix2x2& matrix);
[[nodiscard]]
Matrix2x2 operator+(const Matrix2x2& m1, const Matrix2x2& m2);
[[nodiscard]]
Matrix2x2 operator-(const Matrix2x2& m1, const Matrix2x2& m2);
[[nodiscard]]
Matrix2x2 operator*(const Matrix2x2& m, const float scalar);
[[nodiscard]]
Matrix2x2 operator*(const Matrix2x2& m1, const Matrix2x2& m2);

Matrix2x2& operator+=(Matrix2x2& m1, const Matrix2x2& m2);
Matrix2x2& operator-=(Matrix2x2& m1, const Matrix2x2& m2);
Matrix2x2& operator*=(Matrix2x2& m, const float scalar);
Matrix2x2& operator*=(Matrix2x2& m1, const Matrix2x2& m2);

std::ostream& operator<<(std::ostream& out, const Matrix2x2& m);
