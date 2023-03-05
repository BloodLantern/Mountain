#pragma once

#include <ostream>
#include <compare>
#include <vector>

class Vector2;
class Vector3;
class Matrix;

/// @brief The Vector class represents either a M-dimensional vector or a point.
class Vector
{
public:
    /// @brief Creates a 1x1 null vector
    Vector() : Vector(1, 1) {};
    Vector(const size_t size, const float defaultValue = 0.f);
    /// @brief Copies the content of the given vector to this one.
    Vector(const Vector& vector);
    /// @brief Creates a vector with the data from the given initializer list.
    constexpr Vector(const std::initializer_list<float> data)
        : mData(data), mSize(data.size()) {}
    Vector(const Vector& p1, const Vector& p2);

	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float Norm() const;
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	float SquaredNorm() const;
	/// @brief Returns a normalized vector.
	/// @return A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector Normalize() const;

    /// @brief Returns a Vector2 representing the size of this matrix. This operation
    ///        casts two size_t to floats and therefore might be inaccurate if used
    ///        with huge numbers.
    [[nodiscard]]
    constexpr size_t GetSize() const { return mSize; }

	/// @brief Returns a · b.
	[[nodiscard]]
	static float DotProduct(const Vector& a, const Vector& b);
	/// @brief Returns a x b.
	[[nodiscard]]
	static Vector CrossProduct(const Vector& a, const Vector& b);

	[[nodiscard]]
	float  operator[](const size_t i) const;
	[[nodiscard]]
	float& operator[](const size_t i);
    /// @brief Sets the first element of the vector to the given value.
    Vector& operator=(const float value);
    explicit operator Vector2() const;
    explicit operator Vector3() const;
    operator Matrix() const;

private:
    std::vector<float> mData;
    size_t mSize;
};

[[nodiscard]]
Vector operator+(const Vector& a, const Vector& b);
[[nodiscard]]
Vector operator-(const Vector& a, const Vector& b);
[[nodiscard]]
Vector operator-(const Vector& a);
[[nodiscard]]
Vector operator*(const Vector& a, const Vector& b);
[[nodiscard]]
Vector operator*(const Vector& v, const float factor);
[[nodiscard]]
Vector operator/(const Vector& a, const Vector& b);
[[nodiscard]]
Vector operator/(const Vector& v, const float factor);

Vector& operator+=(Vector& a, const Vector& b);
Vector& operator+=(Vector& v, const float factor);
Vector& operator-=(Vector& a, const Vector& b);
Vector& operator-=(Vector& v, const float factor);
Vector& operator*=(Vector& a, const Vector& b);
Vector& operator*=(Vector& v, const float factor);
Vector& operator/=(Vector& a, const Vector& b);
Vector& operator/=(Vector& v, const float factor);

std::ostream& operator<<(std::ostream& out, const Vector& v);
