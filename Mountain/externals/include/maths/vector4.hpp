#pragma once

#include <ostream>
#include <compare>
#include <cassert>

class Vector2;
class Vector3;
template<size_t M>
class Vector;
class Matrix4x4;

/// @brief The Vector4 class represents either a four-dimensional vector or a point.
class Vector4
{
public:
	float x, y, z, w;

	static constexpr Vector4 UnitX() { return Vector4(1.0f, 0.0f, 0.0f, 0.0f); }
	static constexpr Vector4 UnitY() { return Vector4(0.0f, 1.0f, 0.0f, 0.0f); }
	static constexpr Vector4 UnitZ() { return Vector4(0.0f, 0.0f, 1.0f, 0.0f); }
	static constexpr Vector4 UnitW() { return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }

	constexpr Vector4()	: x(0), y(0), z(0), w(0) {}
	/// @brief Constructs a Vector4 with all its components set to 'xyzw'.
	constexpr Vector4(const float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
	constexpr Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
	constexpr Vector4(const std::initializer_list<float>& values)
	{
		assert(values.size() == 4 && "Cannot initialize Vector4 from initializer list with size != 4");

		const float* it = values.begin();
		x = it[0];
		y = it[1];
		z = it[2];
		w = it[3];
	}
	/// @brief Constructs a Vector4 from point 'p1' to point 'p2'
	Vector4(const Vector4& p1, const Vector4& p2);

	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float Norm() const;
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	float SquaredNorm() const;
	/// @brief Normalizes the vector.
	/// @return A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector4 Normalized() const;
	/// @brief Returns the dot product of this Vector4& with 'other'.
	[[nodiscard]]
	float Dot(const Vector4& other) const;

	/// @brief Returns a · b.
	[[nodiscard]]
	static float Dot(const Vector4& a, const Vector4& b);

	[[nodiscard]]
	float  operator[](const size_t i) const;
	[[nodiscard]]
	float& operator[](const size_t i);
    explicit operator Vector2() const;
    explicit operator Vector3() const;
    operator Vector<4>() const;
    explicit operator Matrix4x4() const;

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Vector4& a, const Vector4& b) = default;
};

[[nodiscard]]
Vector4 operator+(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator-(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator-(const Vector4& a);
[[nodiscard]]
Vector4 operator*(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator*(const Vector4& v, const float factor);
[[nodiscard]]
Vector4 operator*(const Vector4& v, const Matrix4x4& m);
[[nodiscard]]
Vector4 operator/(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator/(const Vector4& v, const float factor);

Vector4& operator+=(Vector4& a, const Vector4& b);
Vector4& operator+=(Vector4& v, const float factor);
Vector4& operator-=(Vector4& a, const Vector4& b);
Vector4& operator-=(Vector4& v, const float factor);
Vector4& operator*=(Vector4& a, const Vector4& b);
Vector4& operator*=(Vector4& v, const float factor);
Vector4& operator*=(Vector4& v, const Matrix4x4& m);
Vector4& operator/=(Vector4& a, const Vector4& b);
Vector4& operator/=(Vector4& v, const float factor);

bool operator==(const Vector4& v, const float f);
bool operator!=(const Vector4& v, const float f);
bool operator<(const Vector4& v, const float f);
bool operator>(const Vector4& v, const float f);
bool operator<=(const Vector4& v, const float f);
bool operator>=(const Vector4& v, const float f);

std::ostream& operator<<(std::ostream& out, const Vector4& v);
