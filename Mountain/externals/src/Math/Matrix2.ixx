export module Math:Matrix2;

import "Math/Core.hpp";

import std;
export import :Types;
export import :Vector2;
export import :Vector3;
import :Calc;

/// @file Matrix3.ixx
/// @brief Defines the Matrix2 struct.

/// @brief The Matrix2 struct represents a 3x3 array mainly used for mathematical operations.
///
/// Matrices are stored using the column-major convention.
export struct MATH_API Matrix2
{
    /// @brief The component at position [0, 0] of a Matrix2.
    float_t m00 = 0.f;

    /// @brief The component at position [1, 0] of a Matrix2.
    float_t m10 = 0.f;

    /// @brief The component at position [0, 1] of a Matrix2.
    float_t m01 = 0.f;

    /// @brief The component at position [1, 1] of a Matrix2.
    float_t m11 = 0.f;

    /// @brief Returns the identity %Matrix.
    ///
    /// The identity %Matrix is one with its diagonal set to one and everything else set to zero.
    [[nodiscard]]
    static constexpr Matrix2 Identity() noexcept;

    /// @brief Returns the identity %Matrix.
    ///
    /// The identity %Matrix is one with its diagonal set to one and everything else set to zero.
    static constexpr void Identity(Matrix2* result) noexcept;

    /// @brief Creates a 2D rotation %Matrix around the Z axis from the given angle.
    ///
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix2 RotationZ(float_t angle) noexcept;

    /// @brief Creates a 2D rotation %Matrix around the Z axis from the given angle.
    ///
    /// @param angle The angle in radians.
    /// @param result The output of the function.
    static void RotationZ(float_t angle, Matrix2* result) noexcept;

    /// @brief Creates a 2D rotation %Matrix around the Z axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static constexpr Matrix2 RotationZ(float_t cos, float_t sin) noexcept;

    /// @brief Creates a 2D rotation %Matrix around the Z axis from the given angle.
    ///
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    /// @param result The output of the function.
    static constexpr void RotationZ(float_t cos, float_t sin, Matrix2* result) noexcept;

    /// @brief Creates a 2D scaling %Matrix from the given Vector2.
    [[nodiscard]]
    static constexpr Matrix2 Scaling(const Vector2& scale) noexcept;

    /// @brief Creates a 2D scaling %Matrix from the given Vector2.
    static constexpr void Scaling(const Vector2& scale, Matrix2* result) noexcept;

    /// @brief Creates a Matrix2 with all its values set to 0.
    constexpr Matrix2() = default;

    /// @brief Creates a Matrix2 with all its values set to this default value.
    constexpr explicit Matrix2(float_t defaultValue) noexcept;

    /// @brief Constructs a Matrix2 with its components set to the data pointed by @c data.
    ///
    /// This constructor assumes that @c data is a valid pointer pointing to at least 4 @c float_t values.
    ///
    /// @param data The data where the values for this matrix's components are located.
    constexpr explicit Matrix2(const float_t* data) noexcept;

    /// @brief Constructs a Matrix2 with 2 column vectors.
    constexpr Matrix2(
            const Vector2& c0,
            const Vector2& c1
    ) noexcept;

    /// @brief Constructs a Matrix2 with 16 float_t values.
    constexpr Matrix2(
            float_t m00, float_t m01,
            float_t m10, float_t m11
    ) noexcept;

    /// @brief Gets a pointer to the first value of this Matrix2.
    ///
    /// @returns A pointer to the first value of this Matrix2.
    [[nodiscard]]
    constexpr const float_t* Data() const noexcept;

    /// @brief Gets a pointer to the first value of this Matrix2.
    ///
    /// @returns A pointer to the first value of this Matrix2.
    [[nodiscard]]
    constexpr float_t* Data() noexcept;

    /// @brief Uses the @c std::cout stream to print the values of this matrix in a square-like shape, e.g. by using newlines to make it easier to read.
    void DebugPrint() const noexcept;

    /// @brief Returns whether the Matrix2 has everything except its diagonal set to zero.
    [[nodiscard]]
    constexpr bool_t IsDiagonal() const noexcept;

    /// @brief Returns whether the Matrix2 is the identity matrix.
    ///
    /// If this returns true, Matrix2::Identity() == *this should be true.
    [[nodiscard]]
    constexpr bool_t IsIdentity() const noexcept;

    /// @brief Returns whether this Matrix2 has everything set to zero.
    [[nodiscard]]
    constexpr bool_t IsNull() const noexcept;

    /// @brief Returns whether the Matrix2 is symmetric by its diagonal elements.
    [[nodiscard]]
    constexpr bool_t IsSymmetric() const noexcept;

    /// @brief Returns whether the Matrix2 is symmetric by its diagonal elements but one of the sides is the opposite of the other.
    [[nodiscard]]
    constexpr bool_t IsAntisymmetric() const noexcept;

    /// @brief Returns the diagonal elements of the Matrix2.
    [[nodiscard]]
    constexpr Vector2 Diagonal() const noexcept;

    /// @brief Returns the diagonal elements of the Matrix2.
    constexpr void Diagonal(Vector2* result) const noexcept;

    /// @brief Returns the sum of the diagonal elements of the Matrix2.
    [[nodiscard]]
    constexpr float_t Trace() const noexcept;

    /// @brief Returns the determinant of this Matrix2.
    [[nodiscard]]
    constexpr float_t Determinant() const noexcept;

    /// @brief Switches the Matrix2 by its diagonal elements.
    [[nodiscard]]
    constexpr Matrix2 Transposed() const noexcept;

    /// @brief Switches the Matrix2 by its diagonal elements.
    constexpr void Transposed(Matrix2* result) const noexcept;

    /// @brief Computes the invert of this Matrix2, e.g. @c *this * Inverted() == Identity() is true.
    [[nodiscard]]
    constexpr Matrix2 Inverted() const;

    /// @brief Computes the invert of this Matrix2, e.g. @c *this * Inverted() == Identity() is true.
    constexpr void Inverted(Matrix2* result) const;

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

    /// @brief Converts this Matrix2 to a Matrix3, homogenizing the new row and column.
    [[nodiscard]]
    explicit operator Matrix3() const;

    /// @brief Converts this Matrix2 to a Matrix, homogenizing the new row and column.
    [[nodiscard]]
    explicit operator Matrix() const;

    /// @brief Returns the opposite of a Matrix2.
    constexpr friend Matrix2 operator-(const Matrix2& matrix) noexcept;

    /// @brief Adds the values of two @ref Matrix2 "3x3 Matrices" one by one.
    constexpr friend Matrix2 operator+(const Matrix2& m1, const Matrix2& m2) noexcept;

    /// @brief Subtracts the values of two @ref Matrix2 "Matrices" one by one.
    constexpr friend Matrix2 operator-(const Matrix2& m1, const Matrix2& m2) noexcept;

    /// @brief Multiplies all values of a Matrix by a @p scalar.
    constexpr friend Matrix2 operator*(const Matrix2& m, float_t scalar) noexcept;

    /// @brief Multiplies all values of a Matrix by a @p scalar.
    constexpr friend Matrix2 operator*(float_t factor, const Matrix2& m) noexcept;

    /// @brief Multiplies a Vector2 by a Matrix2.
    constexpr friend Vector2 operator*(const Matrix2& m, Vector2 v) noexcept;

    /// @brief Multiplies two @ref Matrix2 "Matrices".
    constexpr friend Matrix2 operator*(const Matrix2& m1, const Matrix2& m2) noexcept;

    /// @brief Adds two @ref Matrix2 "Matrices" according to @ref operator+(const Matrix&, const Matrix&), placing the result in @p m1.
    constexpr friend Matrix2& operator+=(Matrix2& m1, const Matrix2& m2) noexcept;

    /// @brief Subtracts two @ref Matrix2 "Matrices" according to @ref operator-(const Matrix&, const Matrix&), placing the result in @p m1.
    constexpr friend Matrix2& operator-=(Matrix2& m1, const Matrix2& m2) noexcept;

    /// @brief Multiplies a Matrix by a @p scalar according to @ref operator*(const Matrix&, const float_t), placing the result in @p m.
    constexpr friend Matrix2& operator*=(Matrix2& m, float_t scalar) noexcept;

    /// @brief Multiplies a Matrix by a Vector2 according to @ref operator*(const Matrix&, const Vector2&), placing the result in @p m.
    constexpr friend Vector2& operator*=(const Matrix2& m, Vector2& v) noexcept;

    /// @brief Multiplies two @ref Matrix2 "Matrices" according to @ref operator*(const Matrix&, const Matrix&), placing the result in @p m1.
    constexpr friend Matrix2& operator*=(Matrix2& m1, const Matrix2& m2) noexcept;

    /// @brief	Checks if two Matrices are equal.
    constexpr friend bool_t operator==(const Matrix2& a, const Matrix2& b) noexcept;

    /// @brief Checks if two Matrices are different.
    constexpr friend bool_t operator!=(const Matrix2& a, const Matrix2& b) noexcept;

    /// @brief Streams a Matrix2 into @p out, printing its values one by one on a single line.
    ///
    /// If you instead want a multiline print, you can use Matrix::DebugPrint.
    friend std::ostream& operator<<(std::ostream& out, const Matrix2& m);
};

static_assert(std::is_default_constructible_v<Matrix2>, "Struct Matrix2 must be default constructible.");
static_assert(std::is_copy_constructible_v<Matrix2>, "Struct Matrix2 must be copy constructible.");
static_assert(std::is_move_constructible_v<Matrix2>, "Struct Matrix2 must be move constructible.");
static_assert(std::is_copy_assignable_v<Matrix2>, "Struct Matrix2 must be copy assignable.");
static_assert(std::is_move_assignable_v<Matrix2>, "Struct Matrix2 must be move assignable.");

constexpr Matrix2::Matrix2(const float_t defaultValue) noexcept
    : m00(defaultValue), m10(defaultValue)
    , m01(defaultValue), m11(defaultValue)
{
}

constexpr Matrix2::Matrix2(const float_t* const data) noexcept
    : m00(data[0]), m10(data[1])
    , m01(data[2]), m11(data[3])
{
}

constexpr Matrix2::Matrix2(const Vector2& c0, const Vector2& c1) noexcept
    : m00(c0.x), m10(c1.x)
    , m01(c0.y), m11(c1.y)
{
}

constexpr Matrix2::Matrix2(
    const float_t m00, const float_t m01,
    const float_t m10, const float_t m11
) noexcept
    : m00(m00), m10(m10)
    , m01(m01), m11(m11)
{
}

constexpr Matrix2 Matrix2::Identity() noexcept
{
    return Matrix2(
        1.f, 0.f,
        0.f, 1.f
    );
}

constexpr void Matrix2::Identity(Matrix2* result) noexcept
{
    *result = Matrix2(
        1.f, 0.f,
        0.f, 1.f
    );
}

constexpr Matrix2 Matrix2::RotationZ(const float_t cos, const float_t sin) noexcept
{
    return Matrix2(
        cos,   -sin,
        sin,    cos
    );
}

constexpr void Matrix2::RotationZ(const float_t cos, const float_t sin, Matrix2* result) noexcept
{
    *result = Matrix2(
        cos,   -sin,
        sin,    cos
    );
}

constexpr Matrix2 Matrix2::Scaling(const Vector2 &scale) noexcept
{
    return Matrix2(
        scale.x,     0.f,
        0.f,     scale.y
    );
}

constexpr void Matrix2::Scaling(const Vector2& scale, Matrix2* result) noexcept
{
    *result = Matrix2(
        scale.x,     0.f,
        0.f,     scale.y
    );
}

constexpr const float_t* Matrix2::Data() const noexcept { return &m00; }

constexpr float_t* Matrix2::Data() noexcept { return &m00; }

constexpr bool_t Matrix2::IsDiagonal() const noexcept
{
    return Calc::IsZero(m01) && Calc::IsZero(m10);
}

constexpr bool_t Matrix2::IsIdentity() const noexcept
{
    if (!IsDiagonal())
        return false;

    return Calc::Equals(m00, 1.f) && Calc::Equals(m11, 1.f);
}

constexpr bool_t Matrix2::IsNull() const noexcept
{
    if (!IsDiagonal())
        return false;

    return Calc::IsZero(m00) && Calc::IsZero(m11);
}

constexpr bool_t Matrix2::IsSymmetric() const noexcept
{
    return Calc::Equals(m01, m10);
}

constexpr bool_t Matrix2::IsAntisymmetric() const noexcept
{
    return Calc::Equals(m01, -m10);
}

constexpr Vector2 Matrix2::Diagonal() const noexcept { return Vector2(m00, m11); }

constexpr void Matrix2::Diagonal(Vector2* result) const noexcept { *result = Vector2(m00, m11); }

constexpr float_t Matrix2::Trace() const noexcept { return m00 + m11; }

constexpr float_t Matrix2::Determinant() const noexcept
{
    return m00 * m11 - m10 * m10;
}

constexpr Matrix2 Matrix2::Transposed() const noexcept
{
    return Matrix2(
        m00, m10,
        m01, m11
    );
}

constexpr void Matrix2::Transposed(Matrix2* result) const noexcept
{
    *result = Matrix2(
        m00, m10,
        m01, m11
    );
}

constexpr Matrix2 Matrix2::Inverted() const
{
    Matrix2 result;
    Inverted(&result);
    return result;
}

constexpr void Matrix2::Inverted(Matrix2* result) const
{
    const float_t determinant = Determinant();

    if (determinant == 0.f) [[unlikely]]
        throw std::invalid_argument("Matrix2 isn't invertible");

    *result = Matrix2(m11, -m10, -m01, m00) * (1.f / determinant);
}

constexpr float_t Matrix2::At(const size_t row, const size_t col) const
{
    if (row < 2 && col < 2) [[likely]]
        return Data()[col * 2 + row];

    [[unlikely]]
    throw std::out_of_range("Matrix2 subscript out of range");
}

constexpr float_t& Matrix2::At(const size_t row, const size_t col)
{
    if (row < 2 && col < 2) [[likely]]
        return Data()[col * 2 + row];

    [[unlikely]]
    throw std::out_of_range("Matrix2 subscript out of range");
}

constexpr Vector3 Matrix2::operator[](const size_t col) const
{
    return Vector3(Data() + static_cast<int64_t>(col) * 2);
}

constexpr Vector3& Matrix2::operator[](const size_t col)
{
    // Pointer arithmetic magic to get around not being able to use reinterpret_cast
    return *static_cast<Vector3*>(static_cast<void*>(Data() + static_cast<int64_t>(col) * 2));
}

export [[nodiscard]] constexpr Matrix2 operator-(const Matrix2& matrix) noexcept
{
    return Matrix2(
        -matrix.m00, -matrix.m01,
        -matrix.m10, -matrix.m11
    );
}

export [[nodiscard]] constexpr Matrix2 operator+(const Matrix2& m1, const Matrix2& m2) noexcept
{
    return Matrix2(
        m1.m00 + m2.m00, m1.m01 + m2.m01,
        m1.m10 + m2.m10, m1.m11 + m2.m11
    );
}

export [[nodiscard]] constexpr Matrix2 operator-(const Matrix2& m1, const Matrix2& m2) noexcept { return m1 + -m2; }

export [[nodiscard]] constexpr Matrix2 operator*(const Matrix2& m, const float_t scalar) noexcept
{
    return Matrix2(
        m.m00 * scalar, m.m01 * scalar,
        m.m10 * scalar, m.m11 * scalar
    );
}

export [[nodiscard]] constexpr Matrix2 operator*(const float_t factor, const Matrix2& m) noexcept { return m * factor; }

export [[nodiscard]] constexpr Vector2 operator*(const Matrix2& m, const Vector2 v) noexcept
{
    return Vector2(
        v.x * m.m00 + v.y * m.m01,
        v.x * m.m10 + v.y * m.m11
    );
}

export [[nodiscard]] constexpr Matrix2 operator*(const Matrix2& m1, const Matrix2& m2) noexcept
{
    return Matrix2(
        m1.m00 * m2.m00 + m1.m01 * m2.m10,
        m1.m00 * m2.m01 + m1.m01 * m2.m11,

        m1.m10 * m2.m00 + m1.m11 * m2.m10,
        m1.m10 * m2.m01 + m1.m11 * m2.m11
    );
}

export constexpr Matrix2& operator+=(Matrix2& m1, const Matrix2& m2) noexcept { return m1 = m1 + m2; }

export constexpr Matrix2& operator-=(Matrix2& m1, const Matrix2& m2) noexcept { return m1 = m1 - m2; }

export constexpr Matrix2& operator*=(Matrix2& m, const float_t scalar) noexcept { return m = m * scalar; }

export constexpr Vector2& operator*=(const Matrix2& m, Vector2& v) noexcept { return v = m * v; }

export constexpr Matrix2& operator*=(Matrix2& m1, const Matrix2& m2) noexcept { return m1 = m1 * m2; }

export [[nodiscard]] constexpr bool_t operator==(const Matrix2& a, const Matrix2& b) noexcept
{
    return a.m00 == b.m00 && a.m01 == b.m01
        && a.m10 == b.m10 && a.m11 == b.m11;
}

export [[nodiscard]] constexpr bool_t operator!=(const Matrix2& a, const Matrix2& b) noexcept { return !(a == b); }

export template <>
struct std::formatter<Matrix2>
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
    typename FmtContext::iterator format(Matrix2 m, FmtContext& ctx) const
    {
        std::ostringstream out;

        const char_t separator = m_Multiline ? '\n' : ' ';

        out << std::vformat(
                "[ {:" + m_Format + "} ; {:" + m_Format + "} ]" + separator
                + "[ {:" + m_Format + "} ; {:" + m_Format + "} ]",
                std::make_format_args(
                        m.m00, m.m01,
                        m.m10, m.m11
                )
        );

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }

private:
    std::string m_Format;
    bool_t m_Multiline = false;
};
