#pragma once

#include <ostream>
#include <compare>
#include <cassert>

class Vector2;
class Vector2i;
template<size_t M>
class Vector;
class Matrix3x3;

/// @brief The Vector3 class represents either a three-dimensional vector or a point.
class Vector3
{
public:
	float x, y, z;

	static constexpr Vector3 UnitX() { return Vector3(1.0f, 0.0f, 0.0f); }
	static constexpr Vector3 UnitY() { return Vector3(0.0f, 1.0f, 0.0f); }
	static constexpr Vector3 UnitZ() { return Vector3(0.0f, 0.0f, 1.0f); }

	constexpr Vector3()	: x(0), y(0), z(0) {}
	/// @brief Constructs a Vector3 with all its components set to 'xyz'.
	constexpr Vector3(const float xyz) : x(xyz), y(xyz), z(xyz) {}
	constexpr Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	constexpr Vector3(const std::initializer_list<float>& values)
	{
		assert(values.size() == 3 && "Cannot initialize Vector3 from initializer list with size != 3");

		const float* it = values.begin();
		x = it[0];
		y = it[1];
		z = it[2];
	}
	/// @brief Constructs a Vector3 from point 'p1' to point 'p2'
	Vector3(const Vector3& p1, const Vector3& p2);

	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float Norm() const;
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	float SquaredNorm() const;
	/// @brief Normalizes the vector.
	/// @return A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector3 Normalized() const;
	/// @brief Returns the dot product of this Vector3& with 'other'.
	[[nodiscard]]
	float Dot(const Vector3& other) const;
	/// @brief Returns the cross product of this Vector3& with 'other'.
	[[nodiscard]]
	Vector3 Cross(const Vector3& other) const;
	/// @brief Rotates the vector by the specified angle around an axis.
	/// @param angle The angle in radians.
	[[nodiscard]]
	Vector3 Rotate(const float angle, const Vector3& axis) const;
	/// @brief Rotates the vector by the specified angle around a center and an axis.
	/// @param angle The angle in radians.
	[[nodiscard]]
	Vector3 Rotate(const float angle, const Vector3& center, const Vector3& axis) const;
	/// @brief Rotates the vector by the specified cosine and sine around an axis.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
	[[nodiscard]]
	Vector3 Rotate(const float cos, const float sin, const Vector3& axis) const;
	/// @brief Rotates the vector by the specified cosine and sine around a center and an axis.
	/// @param cos The cosine of the angle in radians.
	/// @param sin The sine of the angle in radians.
	[[nodiscard]]
	Vector3 Rotate(const float cos, const float sin, const Vector3& axis, const Vector3& center) const;

	/// @brief Returns the angle between 'a' and 'b'.
	[[nodiscard]]
	static float Angle(const Vector3& a, const Vector3& b);
	/// @brief Returns a · b.
	[[nodiscard]]
	static float Dot(const Vector3& a, const Vector3& b);
	/// @brief Returns a x b.
	[[nodiscard]]
	static Vector3 Cross(const Vector3& a, const Vector3& b);

	[[nodiscard]]
	float  operator[](const size_t i) const;
	[[nodiscard]]
	float& operator[](const size_t i);
    explicit operator Vector2() const;
    explicit operator Vector2i() const;
    operator Vector<3>() const;
    explicit operator Matrix3x3() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Vector3& a, const Vector3& b) = default;
};

[[nodiscard]]
Vector3 operator+(const Vector3& a, const Vector3& b);
[[nodiscard]]
Vector3 operator-(const Vector3& a, const Vector3& b);
[[nodiscard]]
Vector3 operator-(const Vector3& a);
[[nodiscard]]
Vector3 operator*(const Vector3& a, const Vector3& b);
[[nodiscard]]
Vector3 operator*(const Vector3& v, const float factor);
[[nodiscard]]
Vector3 operator*(const Vector3& v, const Matrix3x3& m);
[[nodiscard]]
Vector3 operator/(const Vector3& a, const Vector3& b);
[[nodiscard]]
Vector3 operator/(const Vector3& v, const float factor);

Vector3& operator+=(Vector3& a, const Vector3& b);
Vector3& operator+=(Vector3& v, const float factor);
Vector3& operator-=(Vector3& a, const Vector3& b);
Vector3& operator-=(Vector3& v, const float factor);
Vector3& operator*=(Vector3& a, const Vector3& b);
Vector3& operator*=(Vector3& v, const float factor);
Vector3& operator/=(Vector3& a, const Vector3& b);
Vector3& operator/=(Vector3& v, const float factor);

bool operator==(const Vector3& v, const float f);
bool operator!=(const Vector3& v, const float f);
bool operator<(const Vector3& v, const float f);
bool operator>(const Vector3& v, const float f);
bool operator<=(const Vector3& v, const float f);
bool operator>=(const Vector3& v, const float f);

std::ostream& operator<<(std::ostream& out, const Vector3& v);
