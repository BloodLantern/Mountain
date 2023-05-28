#pragma once

#include <ostream>
#include <compare>
#include <cassert>

class Vector2i;
class Vector3;
template<size_t M>
class Vector;
class Matrix2x2;

/// @brief The Vector2 class represents either a two-dimensional vector or a point.
class Vector2
{
public:
	float x, y;

	static constexpr Vector2 UnitX() { return Vector2(1.0f, 0.0f); }
	static constexpr Vector2 UnitY() { return Vector2(0.0f, 1.0f); }

	constexpr Vector2()	: x(0), y(0) {}
	/// @brief Constructs a Vector2 with both its components set to 'xy'.
	constexpr Vector2(const float xy) : x(xy), y(xy) {}
	constexpr Vector2(const float x, const float y) : x(x), y(y) {}
	constexpr Vector2(const std::initializer_list<float>& values)
	{
		assert(values.size() == 2 && "Cannot initialize Vector2 from initializer list with size != 2");

		const float* it = values.begin();
		x = it[0];
		y = it[1];
	}
	/// @brief Constructs a Vector2 from point 'p1' to point 'p2'
	Vector2(const Vector2 p1, const Vector2 p2);

	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float Norm() const;
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	float SquaredNorm() const;
	/// @brief Returns a normalized vector.
	/// @return A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector2 Normalized() const;
	/// @brief Returns the normal vector to this one.
	/// @return A vector with the same length but a normal direction.
	[[nodiscard]]
	Vector2 Normal() const;
	/// @brief Returns the dot product of this Vector2 with 'other'.
	[[nodiscard]]
	float Dot(const Vector2 other) const;
	/// @brief Returns the cross product of this Vector2 with 'other'.
	[[nodiscard]]
	float Cross(const Vector2 other) const;
	/// @brief Returns the determinant of this Vector2 with 'other'.
	[[nodiscard]]
	float Determinant(const Vector2 other) const;
	/// @brief Returns the angle between the beginning and the end of this vector.
	/// @return An angle in radians.
	[[nodiscard]]
	float Angle() const;
	/// @brief Rotates the vector by the specified angle.
	/// @param angle The angle in radians.
	[[nodiscard]]
	Vector2 Rotate(const float angle) const;
	/// @brief Rotates the vector by the specified angle around a center.
	/// @param angle The angle in radians.
	[[nodiscard]]
	Vector2 Rotate(const float angle, const Vector2 center) const;
	/// @brief Rotates the vector by the specified cosine and sine around a center.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
	[[nodiscard]]
	Vector2 Rotate(const float cos, const float sin) const;
	/// @brief Rotates the vector by the specified cosine and sine.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
	[[nodiscard]]
	Vector2 Rotate(const Vector2 center, const float cos, const float sin) const;

	/// @brief Returns the angle between 'a' and 'b'.
	[[nodiscard]]
	static float Angle(const Vector2 a, const Vector2 b);
	/// @brief Returns a · b.
	[[nodiscard]]
	static float Dot(const Vector2 a, const Vector2 b);
	/// @brief Returns a x b.
	[[nodiscard]]
	static float Cross(const Vector2 a, const Vector2 b);
	/// @brief Returns the determinant of 'a' and 'b'.
	[[nodiscard]]
	static float Determinant(const Vector2 a, const Vector2 b);

	[[nodiscard]]
	float  operator[](const size_t i) const;
	[[nodiscard]]
	float& operator[](const size_t i);
	explicit operator Vector2i() const;
    operator Vector3() const;
	operator Vector<2>() const;
	explicit operator Matrix2x2() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Vector2& a, const Vector2& b) = default;
};

[[nodiscard]]
Vector2 operator+(const Vector2 a, const Vector2 b);
[[nodiscard]]
Vector2 operator-(const Vector2 a, const Vector2 b);
[[nodiscard]]
Vector2 operator-(const Vector2 a);
[[nodiscard]]
Vector2 operator*(const Vector2 a, const Vector2 b);
[[nodiscard]]
Vector2 operator*(const Vector2 v, const float factor);
[[nodiscard]]
Vector2 operator*(const Vector2& v, const Matrix2x2& m);
[[nodiscard]]
Vector2 operator/(const Vector2 a, const Vector2 b);
[[nodiscard]]
Vector2 operator/(const Vector2 v, const float factor);

Vector2& operator+=(Vector2& a, const Vector2 b);
Vector2& operator+=(Vector2& v, const float factor);
Vector2& operator-=(Vector2& a, const Vector2 b);
Vector2& operator-=(Vector2& v, const float factor);
Vector2& operator*=(Vector2& a, const Vector2 b);
Vector2& operator*=(Vector2& v, const float factor);
Vector2& operator/=(Vector2& a, const Vector2 b);
Vector2& operator/=(Vector2& v, const float factor);

bool operator==(const Vector2& v, const float f);
bool operator!=(const Vector2& v, const float f);
bool operator<(const Vector2& v, const float f);
bool operator>(const Vector2& v, const float f);
bool operator<=(const Vector2& v, const float f);
bool operator>=(const Vector2& v, const float f);

std::ostream& operator<<(std::ostream& out, const Vector2 v);
