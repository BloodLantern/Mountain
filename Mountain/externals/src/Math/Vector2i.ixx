export module Math:Vector2i;

import "Math/Core.hpp";

import std;
export import :Types;
export import :Vector2;

/// @file Vector2i.ixx
/// @brief Defines the Vector2i struct.

// ReSharper disable once CppInconsistentNaming
/// @brief The Vector2i struct represents either a two-dimensional vector or a point using integers.
export struct MATH_API Vector2i
{
    /// @brief The @c x component of this Vector2i.
    int32_t x = 0;

    /// @brief The @c y component of this Vector2i.
    int32_t y = 0;

    /// @brief Equivalent to calling the default constructor.
    [[nodiscard]]
    static constexpr Vector2i Zero() noexcept;

    /// @brief Returns a Vector2i with @c x @c = @c 1, @c y @c = @c 0.
    [[nodiscard]]
    static constexpr Vector2i UnitX() noexcept;

    /// @brief Returns a Vector2i with @c x @c = @c 0, @c y @c = @c 1.
    [[nodiscard]]
    static constexpr Vector2i UnitY() noexcept;

    /// @brief Returns a Vector2i with both its components set to @c 1.
    [[nodiscard]]
    static constexpr Vector2i One() noexcept;

    /// @brief Returns @p a · @p b.
    [[nodiscard]]
    static constexpr float_t Dot(Vector2i a, Vector2i b) noexcept;

    /// @brief Returns @p a x @p b.
    ///
    /// For a Vector2i this is only the determinant.
    [[nodiscard]]
    static constexpr float_t Cross(Vector2i a, Vector2i b) noexcept;

    /// @brief Returns the determinant of @p a and @p b.
    [[nodiscard]]
    static constexpr float_t Determinant(Vector2i a, Vector2i b) noexcept;

    constexpr Vector2i() = default;

    // ReSharper disable once CppNonExplicitConvertingConstructor
    /// @brief Constructs a Vector2i with both its components set to @p xy.
    explicit constexpr Vector2i(int32_t xy);

    /// @brief Constructs a Vector2i with its components set to the data point32_ted by @c data.
    ///
    /// This constructor assumes that @c data is a valid pointer pointing to at least two @c int32_t values.
    ///
    /// @param data The data where the values for this vector's components are located.
    constexpr explicit Vector2i(const int32_t* data) noexcept;

    /// @brief Constructs a Vector2i with set component values.
    ///
    /// @param x The value to set this vector's x to.
    /// @param y The value to set this vector's y to.
    constexpr Vector2i(int32_t x, int32_t y);

    /// @brief 	Gets a pointer to the first component of this vector.
    /// @returns A pointer to the first component of this vector.
    [[nodiscard]]
    constexpr const int32_t* Data() const noexcept;

    /// @brief 	Gets a pointer to the first component of this vector.
    ///
    /// @returns A pointer to the first component of this vector.
    [[nodiscard]]
    constexpr int32_t* Data() noexcept;

    /// @brief Returns the length of the vector.
    [[nodiscard]]
    float_t Length() const noexcept;

    /// @brief Returns the squared length of the vector.
    [[nodiscard]]
    constexpr float_t SquaredLength() const noexcept;

    /// @brief Returns a normalized vector.
    ///
    /// @returns A vector with the same direction but a length of one.
    [[nodiscard]]
    Vector2 Normalized() const;

    /// @brief Returns the normal vector to this one.
    ///
    /// @returns A vector with the same length but a normal direction.
    [[nodiscard]]
    Vector2 Normal() const;

    /// @brief 	Retrieves this vector's component at index i.
    ///
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    ///
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr int32_t operator[](size_t i) const;

    /// @brief 	Retrieves this vector's component at index i.
    ///
    /// @param i The index of the component to get. It would be 0 for x, 1 for y, etc...
    ///
    /// @returns The value of the component at index i.
    [[nodiscard]]
    constexpr int32_t& operator[](size_t i);

    // ReSharper disable once CppNonExplicitConversionOperator
    /// @brief Converts this Vector2i to a Vector2.
    operator Vector2() const;

    /// @brief Converts this Vector2i to a Vector3 by giving it a @c z value of @c 0.
    explicit operator Vector3() const;

    /// @brief Converts this Vector2i to a Vector4 by giving it a @c z value of @c 0 and a @c w value of @c 1.
    explicit operator Vector4() const;

    /// @brief Adds two Vector2i together.
    constexpr friend Vector2i operator+(Vector2i a, Vector2i b) noexcept;

    /// @brief Returns the opposite of a Vector2i.
    constexpr friend Vector2i operator-(Vector2i a) noexcept;

    /// @brief Subtracts a Vector2i from another one.
    constexpr friend Vector2i operator-(Vector2i a, Vector2i b) noexcept;

    /// @brief Multiplies two Vector2i component-wise.
    constexpr friend Vector2i operator*(Vector2i a, Vector2i b) noexcept;

    /// @brief Multiplies a Vector2i by a @p factor.
    constexpr friend Vector2i operator*(Vector2i v, int32_t factor) noexcept;

    /// @brief Multiplies a Vector2i by a @p factor.
    constexpr friend Vector2i operator*(int32_t factor, Vector2i v) noexcept;

    /// @brief Multiplies a Vector2i by a @p factor.
    constexpr friend Vector2 operator*(Vector2i v, float_t factor) noexcept;

    /// @brief Multiplies a Vector2i by a @p factor.
    constexpr friend Vector2 operator*(float_t factor, Vector2i v) noexcept;

    /// @brief Divides a Vector2i by another one.
    constexpr friend Vector2i operator/(Vector2i a, Vector2i b) noexcept;

    /// @brief Divides a Vector2i by a @p factor.
    constexpr friend Vector2i operator/(Vector2i v, int32_t factor) noexcept;

    /// @brief Divides a Vector2i by a Vector2.
    constexpr friend Vector2 operator/(Vector2i a, Vector2 b) noexcept;

    /// @brief Divides a Vector2i by a @p factor.
    constexpr friend Vector2 operator/(Vector2i v, float_t factor) noexcept;

    /// @brief Adds two Vector2i according to @c operator+(const Vector2i, const Vector2i), placing the result in @p a.
    constexpr friend Vector2i& operator+=(Vector2i& a, Vector2i b) noexcept;

    /// @brief Subtracts a Vector2i from another one according to @c operator-(const Vector2i, const Vector2i), placing the result in @p a.
    constexpr friend Vector2i &operator-=(Vector2i &a, Vector2i b) noexcept;

    /// @brief Multiplies two Vector2i component-wise, according to @c operator*(const, Vector2i, const Vector2i), placing the result in @p a.
    constexpr friend Vector2i& operator*=(Vector2i& a, Vector2i b) noexcept;

    /// @brief Multiplies a Vector2i by a @p factor according to @c operator*(const Vector2i, const int32_t), placing the result in @p v.
    constexpr friend Vector2i& operator*=(Vector2i& v, int32_t factor) noexcept;

    /// @brief Checks if two Vector2i are considered equal using @c Calc::Equals.
    constexpr friend bool_t operator==(Vector2i a, Vector2i b) noexcept;

    /// @brief Checks if two Vector2i are considered different using @c Calc::Equals.
    constexpr friend bool_t operator!=(Vector2i a, Vector2i b) noexcept;

    /// @brief Streams a Vector2i into @p out, printing its values one by one on a single line.
    friend std::ostream& operator<<(std::ostream& out, Vector2i v) noexcept;
};

static_assert(std::is_default_constructible_v<Vector2i>, "Struct Vector2i must be default constructible.");
static_assert(std::is_copy_constructible_v<Vector2i>, "Struct Vector2i must be copy constructible.");
static_assert(std::is_move_constructible_v<Vector2i>, "Struct Vector2i must be move constructible.");
static_assert(std::is_copy_assignable_v<Vector2i>, "Struct Vector2i must be copy assignable.");
static_assert(std::is_move_assignable_v<Vector2i>, "Struct Vector2i must be move assignable.");

constexpr Vector2i::Vector2i(const int32_t xy): x(xy), y(xy) {}

constexpr Vector2i::Vector2i(const int32_t* const data) noexcept : x(data[0]), y(data[1]) {}

constexpr Vector2i::Vector2i(const int32_t x, const int32_t y): x(x), y(y) {}

constexpr Vector2i Vector2i::Zero() noexcept { return Vector2i(); }

constexpr Vector2i Vector2i::UnitX() noexcept { return Vector2i(1, 0); }

constexpr Vector2i Vector2i::UnitY() noexcept { return Vector2i(0, 1); }

constexpr Vector2i Vector2i::One() noexcept { return Vector2i(1); }

constexpr float_t Vector2i::Dot(const Vector2i a, const Vector2i b) noexcept { return static_cast<float_t>(a.x * b.x + a.y * b.y); }

constexpr float_t Vector2i::Cross(const Vector2i a, const Vector2i b) noexcept { return Determinant(a, b); }

constexpr float_t Vector2i::Determinant(const Vector2i a, const Vector2i b) noexcept { return static_cast<float_t>(a.x * b.y - b.x * a.y); }

constexpr const int32_t* Vector2i::Data() const noexcept { return &x; }

constexpr int32_t* Vector2i::Data() noexcept { return &x; }

constexpr float_t Vector2i::SquaredLength() const noexcept { return static_cast<float_t>(x * x + y * y); }

constexpr int32_t Vector2i::operator[](const size_t i) const
{
    if (i < 2) [[likely]]
        return *(Data() + i);
    [[unlikely]]
        throw std::out_of_range("Vector2i subscript out of range");
}

constexpr int32_t& Vector2i::operator[](const size_t i)
{
    if (i < 2) [[likely]]
        return *(Data() + i);
    [[unlikely]]
        throw std::out_of_range("Vector2i subscript out of range");
}

export [[nodiscard]] constexpr Vector2i operator+(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x + b.x, a.y + b.y); }

export [[nodiscard]] constexpr Vector2i operator-(const Vector2i a) noexcept { return Vector2i(-a.x, -a.y); }

export [[nodiscard]] constexpr Vector2i operator-(const Vector2i a, const Vector2i b) noexcept { return a + -b; }

export [[nodiscard]] constexpr Vector2i operator*(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x * b.x, a.y * b.y); }

export [[nodiscard]] constexpr Vector2i operator*(const Vector2i v, const int32_t factor) noexcept { return Vector2i(v.x * factor, v.y * factor); }

export [[nodiscard]] constexpr Vector2i operator*(const int32_t factor, const Vector2i v) noexcept { return v * factor; }

export [[nodiscard]] constexpr Vector2 operator*(const Vector2i v, const float_t factor) noexcept
{
    return Vector2(static_cast<float_t>(v.x) * factor, static_cast<float_t>(v.y) * factor);
}

export [[nodiscard]] constexpr Vector2 operator*(const float_t factor, const Vector2i v) noexcept { return v * factor; }

export [[nodiscard]] constexpr Vector2i operator/(const Vector2i a, const Vector2i b) noexcept { return Vector2i(a.x / b.x, a.y / b.y); }

export [[nodiscard]] constexpr Vector2i operator/(const Vector2i v, const int32_t factor) noexcept { return Vector2i(v.x / factor, v.y / factor); }

export [[nodiscard]] constexpr Vector2 operator/(const Vector2i a, const Vector2 b) noexcept
{
    return Vector2(static_cast<float_t>(a.x) / static_cast<float_t>(b.x), static_cast<float_t>(a.y) / static_cast<float_t>(b.y));
}

export [[nodiscard]] constexpr Vector2 operator/(const Vector2i v, const float_t factor) noexcept
{
    return Vector2(static_cast<float_t>(v.x) / factor, static_cast<float_t>(v.y) / factor);
}

export constexpr Vector2i& operator+=(Vector2i& a, const Vector2i b) noexcept { return a = a + b; }

export constexpr Vector2i &operator-=(Vector2i &a, const Vector2i b) noexcept { return a = a - b; }

export constexpr Vector2i& operator*=(Vector2i& a, const Vector2i b) noexcept { return a = a * b; }

export constexpr Vector2i& operator*=(Vector2i& v, const int32_t factor) noexcept { return v = v * factor; }

export [[nodiscard]] constexpr bool_t operator==(const Vector2i a, const Vector2i b) noexcept { return a.x == b.x && a.y == b.y; }

export [[nodiscard]] constexpr bool_t operator!=(const Vector2i a, const Vector2i b) noexcept { return !(a == b); }

export template<> struct std::formatter<Vector2i>
{
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx);

    template <class FmtContext>
    typename FmtContext::iterator format(Vector2i v, FmtContext& ctx) const;

private:
    std::string m_Format;
};

template <class ParseContext>
constexpr typename ParseContext::iterator std::formatter<Vector2i, char_t>::parse(ParseContext& ctx)
{
    auto it = ctx.begin();
    if (it == ctx.end())
        return it;

    while (*it != '}' && it != ctx.end())
        m_Format += *it++;

    return it;
}

template <class FmtContext>
typename FmtContext::iterator std::formatter<Vector2i>::format(Vector2i v, FmtContext &ctx) const
{
    std::ostringstream out;

    out << std::vformat("{:" + m_Format + "} ; {:" + m_Format + '}', std::make_format_args(v.x, v.y));

    return std::ranges::copy(std::move(out).str(), ctx.out()).out;
}
