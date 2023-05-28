#pragma once

#include "vector.hpp"
#include "vector2.hpp"
#include "vector2i.hpp"
#include "vector3.hpp"
#include "matrix2x2.hpp"
#include "matrix3x3.hpp"
#include "matrix4x4.hpp"

#include <cassert>
#include <iostream>
#include <type_traits>

#define SQ(var) ((var) * (var))

/// @brief The Matrix class represents a two-dimensional array mainly used for mathematical operations.
///        The easiest way to create a matrix is to use the std::initializer_list constructor which allows
///        us to do the following for a 3x3 identity matrix: Matrix m = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } }.
template<size_t M, size_t N = M>
class Matrix
{
public:
    /// @brief Returns the identity matrix for the given size.
    ///        The identity matrix is a matrix with its diagonal
    ///        set to one and everything else set to zero.
    ///        Thi function is only defined for square matrices
    template<typename = std::enable_if_t<(M == N)>>
    static constexpr Matrix<M, N> Identity()
    {
        __assume(M == N);

        Matrix<M, N> result;
        for (size_t i = 0; i < M; i++)
            result[i][i] = 1;
        return result;
    }

#pragma region constructors
    Matrix(const float defaultValue = 0.f)
        : mIsSquare(M == N)
    {
        for (size_t i = 0; i < M; i++)
            mData[i] = Vector<N>(defaultValue);
    }

    /// @brief Copies the content of the given matrix to this one.
    Matrix(const Matrix<M, N>& other)
        : mIsSquare(M == N)
    {
        for (size_t i = 0; i < M; i++)
            mData[i] = Vector<N>(other[i]);
    }

    /// @brief Creates a matrix with the data from the given initializer list.
    Matrix(const std::initializer_list<Vector<N>> data)
        : mIsSquare(M == N)
    {
        const Vector<N>* const it = data.begin();
        for (size_t i = 0; i < data.size(); i++)
            mData[i] = it[i];
    }

    template<typename = std::enable_if_t<(M == N)>>
    Matrix(const Matrix2x2& other2x2)
        : mIsSquare(true)
    {
        mData[0] = (Vector<2>) other2x2[0];
        mData[1] = (Vector<2>) other2x2[1];
    }

    template<typename = std::enable_if_t<(M == N)>>
    Matrix(const Matrix3x3& other3x3)
        : mIsSquare(true)
    {
        mData[0] = (Vector<3>) other3x3[0];
        mData[1] = (Vector<3>) other3x3[1];
        mData[2] = (Vector<3>) other3x3[2];
    }

    template<typename = std::enable_if_t<(M == N)>>
    Matrix(const Matrix4x4& other4x4)
        : mIsSquare(true)
    {
        mData[0] = (Vector<4>) other4x4[0];
        mData[1] = (Vector<4>) other4x4[1];
        mData[2] = (Vector<4>) other4x4[2];
        mData[3] = (Vector<4>) other4x4[3];
    }
#pragma endregion

#pragma region functions
    /// @brief Returns whether the matrix has everything except its diagonal set to zero.
    [[nodiscard]]
    bool IsDiagonal() const
    {
        // A matrix can't be diagonal if it isn't a square matrix
        if (!mIsSquare)
            return false;
        __assume(M == N);

        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                if (i != j && mData[i][j] != 0)
                    return false;
        return true;
    }

    /// @brief Returns whether the matrix is the identity matrix.
    ///        If this returns true, Matrix::Identity(size) == *this should be true.
    [[nodiscard]]
    bool IsIdentity() const
    {
        if (!IsDiagonal())
            return false;
        __assume(M == N);

        for (size_t i = 0; i < M; i++)
            if (mData[i][i] != 1)
                return false;
        return true;
    }

    /// @brief Returns wether this matrix has everything set to zero.
    [[nodiscard]]
    bool IsNull() const
    {
        if (!IsDiagonal())
            return false;
        __assume(M == N);

        for (size_t i = 0; i < M; i++)
            if (mData[i][i] != 0)
                return false;
        return true;
    }

    /// @brief Returns whether the matrix is symmetric by its diagonal elements.
    [[nodiscard]]
    bool IsSymmetric() const
    {
        if (!mIsSquare)
            return false;
        __assume(M == N);

        for (size_t i = 0; i < M; i++)
            for (size_t j = i + 1; j < N; j++)
                if (mData[i][j]!= mData[j][i])
                    return false;
        return true;
    }

    /// @brief Returns whether the matrix is symmetric by its diagonal elements
    ///        but one of the sides is the opposite of the other.
    [[nodiscard]]
    bool IsAntisymmetric() const
    {
        if (!mIsSquare)
            return false;
        __assume(M == N);

        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                if (mData[i][j] != -mData[j][i])
                    return false;
        return true;
    }

    /// @brief Returns the diagonal elements of the matrix.
    [[nodiscard]]
    Vector<std::min(M, N)> Diagonal() const
    {
        Vector<std::min(M, N)> result;
        for (size_t i = 0; i < std::min(M, N); i++)
            result[i] = mData[i][i];
        return result;
    }

    /// @brief Returns the sum of the diagonal elements of the matrix.
    [[nodiscard]]
    float Trace() const
    {
        float result = 0.f;
        for (size_t i = 0; i < std::min(M, N); i++)
            result += mData[i][i];
        return result;
    }

    /// @brief Returns a matrix with its data set to the given indices of this one.
    template<size_t _M, size_t _N>
    [[nodiscard]]
    Matrix<_M, _N> SubMatrix(const size_t rowIndex, const size_t colIndex) const
    {
        assert(rowIndex < M && colIndex < N && "Cannot submatrix out of bounds");
        assert(_M > 0 && _N > 0 && "Cannot submatrix of size 0");
        assert(colIndex + _N >= N && "Cannot overflow submatrix columns");
        __assume(rowIndex < M && colIndex < N);
        __assume(_M > 0 && _N > 0);
        __assume(colIndex + _N >= N);

        Matrix<_M, _N> result;
        size_t overflow = rowIndex + _M - M;

        for (size_t i = 0; i < _M; i++)
            for (size_t j = 0; j < _N; j++)
            {
                if (i < overflow)
                    result[i][j] = mData[i][colIndex + j];
                else
                    result[i][j] = mData[rowIndex + i - overflow][colIndex + j];
            }
        return result;
    }

    /// @brief Returns the determinant of this matrix.
    [[nodiscard]]
    float Determinant() const
    {
        assert(mIsSquare && "Cannot calculate the determinant of a non-square matrix");
        __assume(M == N);

        if constexpr (M == 2 && N == 2)
            return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
        else
        {
            float result = 0.f;
            for (size_t i = 0; i < M; i++)
            {
                result += mData[i][0]
                    * SubMatrix<M - 1, N - 1>((i + 1) % M, 1).Determinant()
                    * std::pow(-1.f, (float) i);
            }
            return result;
        }
    }

    /// @brief Sets this matrix to the identity matrix.
    Matrix<M, N>& LoadIdentity()
    {
        assert(mIsSquare);
        __assume(M == N);

        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                mData[i][j] = (i == j ? 1.f : 0.f);
        return *this;
    }

    /// @brief Switches the matrix by its diagonal elements.
    Matrix<N, M>& Transpose() { return *this = Matrix<M, N>::Transpose(*this); }
    /// @brief Adds the given matrix to the right of this one.
    template<size_t _N>
    Matrix<M, N + _N>& Augmented(const Matrix<M, _N>& other) { return *this = Matrix<M, N>::Augmented(other); }

    Matrix<M, N>& GaussJordan() { return *this = Matrix<M, N>::GaussJordan(*this); }

    Matrix<M, N>& Inverse() { return *this = Matrix<M, N>::Inverse(*this); }

    /// @brief Returns a Vector2 representing the size of this matrix. This operation
    ///        casts two size_t to ints and therefore might be inaccurate if used
    ///        with huge numbers.
    [[nodiscard]]
    constexpr Vector2i Size() const { return Vector2i((int) M, (int) N); }

    [[nodiscard]]
    constexpr size_t Rows() const { return M; }

    [[nodiscard]]
    constexpr size_t Cols() const { return N; }

    [[nodiscard]]
    constexpr bool IsSquare() const { return mIsSquare; }

    /// @brief Switches the given matrix by its diagonal elements.
    [[nodiscard]]
    static Matrix<N, M> Transpose(const Matrix<M, N>& matrix)
    {
        Matrix<N, M> result;
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                result[j][i] = matrix[i][j];
        return result;
    }

    /// @brief Adds the 'm2' to the right of 'm1'.
    template<size_t _N>
    [[nodiscard]]
    static Matrix<M, N + _N> Augmented(const Matrix<M, N>& m1, const Matrix<M, _N>& m2)
    {
        Matrix<M, N + _N> result;

        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
                result[i][j] = m1[i][j];
            for (size_t j = 0; j < _N; j++)
                result[i][N + j] = m2[i][j];
        }

        return result;
    }

    /// @brief Computes the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix<M, N> GaussJordan(const Matrix<M, N>& matrix)
    {
        Matrix<M, N> result = matrix;
        
        // Last pivot rank
        size_t r = (size_t) -1;
        // j is the current column
        for (size_t j = 0; j < N; j++)
        {
            // Max value row index
            size_t k = 0;
            {
                float maxValue = 0;
                for (size_t i = r + 1; i < M; i++)
                {
                    float value = result[i][j];
                    if (value == 1)
                    {
                        k = i;
                        break;
                    }

                    if (std::abs(value) > maxValue)
                    {
                        maxValue = value;
                        k = i;
                    }
                }
            }

            float value = result[k][j];
            if (value != 0)
            {
                // r is the next pivot row index
                r++;
                // Normalize the pivot's row
                result[k] /= value;

                if (k != r)
                    // Swap k and r rows
                    for (size_t i = 0; i < N; i++)
                        std::swap(result[k][i], result[r][i]);

                for (size_t i = 0; i < M; i++)
                    if (i != r)
                        result[i] -= result[r] * result[i][j];
            }

            if (r == M - 1)
                break;
        }

        return result;
    }

    /// @brief Computes the inverse of the given matrix using the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix<M, N> Inverse(const Matrix<M, N>& matrix)
    {
        assert(matrix.mIsSquare && "Matrix must be square to get the inverse");
        __assume(M == N);

        if (matrix.Determinant() == 0) [[unlikely]]
            throw std::invalid_argument("Matrix isn't inversible");
        else [[likely]]
        {
            Matrix<M, N * 2> gaussJordan = Matrix<M, N * 2>::GaussJordan(Matrix<M, N>::Augmented(matrix, Matrix<M, N>::Identity()));
            Matrix<M, N> right = gaussJordan.SubMatrix<M, N>(0, N);

            return right;
        }
    }
#pragma endregion

#pragma region operators
    [[nodiscard]]
    constexpr const Vector<N>& operator[](const size_t row) const { return mData[row]; }

    [[nodiscard]]
    constexpr Vector<N>& operator[](const size_t row) { return mData[row]; }

    explicit operator Vector2() const
    {
        assert((M == 2 && N == 1) || (M == 1 && N == 2) && "Matrix must be 2x1 or 1x2 for a cast to Vector2");
        __assume((M == 2 && N == 1) || (M == 1 && N == 2));

        if (M == 2)
            return { mData[0][0], mData[1][0] };
        else
            return { mData[0][0], mData[0][1] };
    }

    explicit operator Vector3() const
    {
        assert((M == 3 && N == 1) || (M == 1 && N == 3) && "Matrix must be 3x1 or 1x3 for a cast to Vector3");
        __assume((M == 3 && N == 1) || (M == 1 && N == 3));

        if (M == 3)
            return { mData[0][0], mData[1][0], mData[2][0] };
        else
            return { mData[0][0], mData[1][0], mData[2][0] };
    }

    explicit operator Vector<M>() const
    {
        assert(N >= 1 && "Matrix must have at least 1 column for a cast to Vector<M>");
        __assume(N >= 1);
        Vector<M> result;

        for (size_t i = 0; i < M; i++)
            result[i] = mData[i][0];

        return result;
    }

    explicit operator Matrix2x2() const
    {
        assert(M >= 2 && N >= 2 && "Matrix must be at least 2x2 for a cast to Matrix2x2");
        __assume(M >= 2 && N >= 2);

        return Matrix2x2(
            mData[0][0], mData[0][1],
            mData[1][0], mData[1][1]
        );
    }
   
    explicit operator Matrix3x3() const
    {
        assert(M >= 3 && N >= 3 && "Matrix must be at least 3x3 for a cast to Matrix3x3");
        __assume(M >= 3 && N >= 3);

        return Matrix3x3(
            mData[0][0], mData[0][1], mData[0][2],
            mData[1][0], mData[1][1], mData[1][2],
            mData[2][0], mData[2][1], mData[2][2]
        );
    }
   
    explicit operator Matrix4x4() const
    {
        assert(M >= 4 && N >= 4 && "Matrix must be at least 4x4 for a cast to Matrix4x4");
        __assume(M >= 4 && N >= 4);

        return Matrix4x4(
            mData[0][0], mData[0][1], mData[0][2], mData[0][3],
            mData[1][0], mData[1][1], mData[1][2], mData[1][3],
            mData[2][0], mData[2][1], mData[2][2], mData[2][3],
            mData[3][0], mData[3][1], mData[3][2], mData[3][3]
        );
    }

    [[nodiscard]]
    Matrix<M, N> operator-() const
    {
        Matrix<M, N> result;
        for (size_t i = 0; i < M; i++)
            result[i] = -mData[i];
        return result;
    }

    [[nodiscard]]
    Matrix<M, N> operator+(const Matrix<M, N>& other) const
    {
        Matrix<M, N> result;
        for (size_t i = 0; i < M; i++)
            result[i] = mData[i] + other[i];
        return result;
    }

    [[nodiscard]]
    Matrix<M, N> operator-(const Matrix<M, N>& other) const
    {
        return *this + (-other);
    }

    [[nodiscard]]
    Matrix<M, N> operator*(const float scalar) const
    {
        Matrix<M, N> result;
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                result[i][j] = mData[i][j] * scalar;
        return result;
    }

    template<size_t _N>
    [[nodiscard]]
    Matrix<M, N> operator*(const Matrix<N, _N>& other) const
    {
        Matrix<M, N> result;
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                for (size_t k = 0; k < N; k++)
                    result[i][j] += mData[i][k] * other[k][j];
        return result;
    }

    Matrix<M, N>& operator+=(const Matrix<M, N>& other)
    {
        return *this = *this + other;
    }

    Matrix<M, N>& operator-=(const Matrix<M, N>& other)
    {
        return *this = *this - other;
    }

    Matrix<M, N>& operator*=(const float scalar)
    {
        return *this = *this * scalar;
    }

    Matrix<M, N>& operator*=(const Matrix<M, N>& other)
    {
        return *this = *this * other;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix<M, N>& m)
    {
        for (size_t i = 0; i < M; i++)
        {
            out << m.mData[i];
            if (i != M - 1)
                out << "\n";
        }
        return out;
    }
#pragma endregion

private:
    Vector<N> mData[M];
    bool mIsSquare;
};

#undef SQ
