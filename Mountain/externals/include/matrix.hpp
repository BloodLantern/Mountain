#pragma once

#include <vector>
#include "vector.hpp"
#include "vector2i.hpp"

class Matrix2x2;
class Matrix3x3;
class Matrix4x4;

/// @brief The Matrix class represents a two-dimensional array mainly used for mathematical operations.
///        The easiest way to create a matrix is to use the std::initializer_list constructor which allows
///        us to do the following for a 3x3 identity matrix: Matrix m = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } }.
class Matrix
{
public:
    /// @brief Returns the identity matrix for the given size.
    ///        The identity matrix is a matrix with its diagonal
    ///        set to one and everything else set to zero.
    static Matrix Identity(const size_t size);

    /// @brief Creates a 1x1 null matrix
    Matrix() : Matrix(1, 1) {};
    Matrix(const size_t rows, const size_t cols = 1, const float defaultValue = 0.f);
    Matrix(const Vector2 size, const float defaultValue = 0.f)
        : Matrix((size_t) size.x, (size_t) size.y, defaultValue) {}
    /// @brief Copies the content of the given matrix to this one.
    Matrix(const Matrix& matrix);
    /// @brief Creates a matrix with the data from the given initializer list.
    Matrix(const std::initializer_list<Vector> data)
        : mData(data), mRows(data.size()), mCols(data.begin()[0].GetSize()), mIsSquare(mRows == mCols) {}

    /// @brief Returns whether the matrix has everything except its diagonal set to zero.
    [[nodiscard]]
    bool IsDiagonal() const;
    /// @brief Returns whether the matrix is the identity matrix.
    ///        If this returns true, Matrix::Identity(size) == *this should be true.
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
    /// @brief Returns the diagonal elements of the matrix. The size of the returned
    ///        matrix is [min(rows, cols), 0].
    [[nodiscard]]
    Vector Diagonal() const;
    /// @brief Returns the sum of the diagonal elements of the matrix.
    [[nodiscard]]
    float Trace() const;
    /// @brief Returns a matrix with its data set to the given indices of this one.
    [[nodiscard]]
    Matrix SubMatrix(const size_t rowIndex, const size_t colIndex, const size_t rows, const size_t cols) const;
    /// @brief Returns the determinant of this matrix.
    [[nodiscard]]
    float Determinant() const;
    /// @brief Sets this matrix to the identity matrix.
    Matrix& Identity(this Matrix& self);
    /// @brief Switches the matrix by its diagonal elements.
    Matrix& Transpose(this Matrix& self);
    /// @brief Adds the given matrix to the right of this one.
    Matrix& Augmented(this Matrix& self, const Matrix& other);
    Matrix& GaussJordan(this Matrix& self);
    Matrix& Inverse(this Matrix& self);

    /// @brief Returns a Vector2 representing the size of this matrix. This operation
    ///        casts two size_t to ints and therefore might be inaccurate if used
    ///        with huge numbers.
    [[nodiscard]]
    constexpr Vector2i GetSize() const { return Vector2i((int) mRows, (int) mCols); }
    [[nodiscard]]
    constexpr size_t GetRows() const { return mRows; }
    [[nodiscard]]
    constexpr size_t GetCols() const { return mCols; }
    /// @brief Returns whether the matrix has the same number of rows and columns.
    [[nodiscard]]
    constexpr bool IsSquare() const { return mIsSquare; }

    /// @brief Switches the given matrix by its diagonal elements.
    [[nodiscard]]
    static Matrix Transpose(const Matrix& matrix);
    /// @brief Adds the 'm2' to the right of 'm1'.
    [[nodiscard]]
    static Matrix Augmented(const Matrix& m1, const Matrix& m2);
    /// @brief Computes the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix GaussJordan(const Matrix& matrix);
    /// @brief Computes the inverse of the given matrix using the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix Inverse(const Matrix& matrix);
    /// @brief Creates a 2D rotation matrix from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix2D(const float angle);
    /// @brief Creates a 2D rotation matrix from the given cosine and sine.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix2D(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix around the X axis from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3DX(const float angle);
    /// @brief Creates a 3D rotation matrix around the X axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3DX(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix around the Y axis from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3DY(const float angle);
    /// @brief Creates a 3D rotation matrix around the Y axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3DY(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix around the Z axis from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3DZ(const float angle);
    /// @brief Creates a 3D rotation matrix around the Z axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3DZ(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix from the given angle and axis.
	/// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3D(const float angle, const Vector3& axis);
    /// @brief Creates a 3D rotation matrix from the given angle for each of the x, y, and z axis.
    [[nodiscard]]
    static Matrix RotationMatrix3D(const Vector3& rotation);
    /// @brief Creates a 3D rotation matrix from the given cosine, sine and axis.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix RotationMatrix3D(const float cos, const float sin, const Vector3& axis);
    /// @brief Creates a 2D scaling matrix from the given Vector2.
    [[nodiscard]]
    static Matrix ScalingMatrix2D(const Vector2 scale);
    /// @brief Creates a 3D scaling matrix from the given Vector3.
    [[nodiscard]]
    static Matrix ScalingMatrix3D(const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    [[nodiscard]]
    static Matrix TRS(const Vector3& translation, const Vector3& rotation, const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
	/// @param rotationAngle The angle in radians.
    [[nodiscard]]
    static Matrix TRS(const Vector3& translation, const float rotationAngle, const Vector3& axis, const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    [[nodiscard]]
    static Matrix TRS(const Vector3& translation, const Matrix& rotation, const Vector3& scale);

    [[nodiscard]]
    constexpr const Vector& operator[](const size_t row) const { return mData[row]; }
    [[nodiscard]]
    constexpr Vector& operator[](const size_t row) { return mData[row]; }
    explicit operator Vector2() const;
    explicit operator Vector3() const;
    explicit operator Vector() const;
    explicit operator Matrix2x2() const;
    explicit operator Matrix3x3() const;
    explicit operator Matrix4x4() const;

private:
    std::vector<Vector> mData;
    size_t mRows;
    size_t mCols;
    bool mIsSquare;
};

[[nodiscard]]
Matrix operator-(const Matrix& matrix);
[[nodiscard]]
Matrix operator+(const Matrix& m1, const Matrix& m2);
[[nodiscard]]
Matrix operator-(const Matrix& m1, const Matrix& m2);
[[nodiscard]]
Matrix operator*(const Matrix& m, const float scalar);
[[nodiscard]]
Matrix operator*(const Matrix& m1, const Matrix& m2);

Matrix& operator+=(Matrix& m1, const Matrix& m2);
Matrix& operator-=(Matrix& m1, const Matrix& m2);
Matrix& operator*=(Matrix& m, const float scalar);
Matrix& operator*=(Matrix& m1, const Matrix& m2);

std::ostream& operator<<(std::ostream& out, const Matrix& m);
