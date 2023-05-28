#pragma once

#include <ostream>
#include <compare>
#include <cassert>

class Vector2;
class Vector3;
template<size_t M>
class Vector;
class Matrix2x2;

/// @brief The Vector2i class represents either a two-dimensional vector or a point.
class Vector2i
{
public:
	int x, y;

	static constexpr Vector2i UnitX() { return Vector2i(1, 0); }
	static constexpr Vector2i UnitY() { return Vector2i(0, 1); }

	constexpr Vector2i() : x(0), y(0) {}
	/// @brief Constructs a Vector2i with both its components set to 'xy'.
	constexpr Vector2i(const int xy) : x(xy), y(xy) {}
	constexpr Vector2i(const int x, const int y) : x(x), y(y) {}
	constexpr Vector2i(const std::initializer_list<int>& values)
	{
		assert(values.size() == 2 && "Cannot initialize Vector2i from initializer list with size != 2");

		const int* it = values.begin();
		x = it[0];
		y = it[1];
	}
	/// @brief Constructs a Vector2i from point 'p1' to point 'p2'
	Vector2i(const Vector2i p1, const Vector2i p2);

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
	/// @brief Returns the dot product of this Vector2i with 'other'.
	[[nodiscard]]
	float Dot(const Vector2i other) const;
	/// @brief Returns the cross product of this Vector2i with 'other'.
	[[nodiscard]]
	float Cross(const Vector2i other) const;
	/// @brief Returns the determinant of this Vector2i with 'other'.
	[[nodiscard]]
	float Determinant(const Vector2i other) const;
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
	Vector2 Rotate(const float angle, const Vector2i center) const;
	/// @brief Rotates the vector by the specified cosine and sine around a center.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
	[[nodiscard]]
	Vector2 Rotate(const float cos, const float sin) const;
	/// @brief Rotates the vector by the specified cosine and sine.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
	[[nodiscard]]
	Vector2 Rotate(const Vector2i center, const float cos, const float sin) const;

	/// @brief Returns the angle between 'a' and 'b'.
	[[nodiscard]]
	static float Angle(const Vector2i a, const Vector2i b);
	/// @brief Returns a · b.
	[[nodiscard]]
	static float Dot(const Vector2i a, const Vector2i b);
	/// @brief Returns a x b.
	[[nodiscard]]
	static float Cross(const Vector2i a, const Vector2i b);
	/// @brief Returns the determinant of 'a' and 'b'.
	[[nodiscard]]
	static float Determinant(const Vector2i a, const Vector2i b);

	[[nodiscard]]
	int  operator[](const size_t i) const;
	[[nodiscard]]
	int& operator[](const size_t i);
    operator Vector2() const;
    operator Vector3() const;
    operator Vector<2>() const;
    explicit operator Matrix2x2() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Vector2i& a, const Vector2i& b) = default;
};

[[nodiscard]]
Vector2i operator+(const Vector2i a, const Vector2i b);
[[nodiscard]]
Vector2i operator-(const Vector2i a, const Vector2i b);
[[nodiscard]]
Vector2i operator-(const Vector2i a);
[[nodiscard]]
Vector2i operator*(const Vector2i a, const Vector2i b);
[[nodiscard]]
Vector2i operator*(const Vector2i v, const int factor);
[[nodiscard]]
Vector2 operator/(const Vector2i a, const Vector2i b);
[[nodiscard]]
Vector2 operator/(const Vector2i v, const float factor);

Vector2i& operator+=(Vector2i& a, const Vector2i b);
Vector2i& operator+=(Vector2i& v, const int factor);
Vector2i& operator-=(Vector2i& a, const Vector2i b);
Vector2i& operator-=(Vector2i& v, const int factor);
Vector2i& operator*=(Vector2i& a, const Vector2i b);
Vector2i& operator*=(Vector2i& v, const int factor);

bool operator==(const Vector2i& v, const int i);
bool operator!=(const Vector2i& v, const int i);
bool operator<(const Vector2i& v, const int i);
bool operator>(const Vector2i& v, const int i);
bool operator<=(const Vector2i& v, const int i);
bool operator>=(const Vector2i& v, const int i);

std::ostream& operator<<(std::ostream& out, const Vector2i v);
