#pragma once

#include <ostream>
#include <compare>

#include "vector2.hpp"
#include "vector3.hpp"

#define SQ(var) ((var) * (var))

/// @brief The Vector class represents either a M-dimensional vector or a point.
template<size_t M>
class Vector
{
public:
#pragma region constructors
    Vector(const float defaultValue = 0.f)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] = defaultValue;
	}

    /// @brief Copies the content of the given vector to this one.
    Vector(const Vector<M>& vector)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] = vector[i];
	}

    /// @brief Creates a vector with the data from the given initializer list.
    constexpr Vector(const std::initializer_list<float> data)
	{
		assert(data.size() == M && "The given initializer list must have the same size as the vector");

		const float* it = data.begin();
		for (size_t i = 0; i < M; i++)
			mData[i] = it[i];
	}
#pragma endregion

#pragma region functions
	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float Norm() const
	{
		return sqrt(SquaredNorm());
	}

	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	float SquaredNorm() const
	{
		float result = 0;
		for (size_t i = 0; i < M; i++)
			result += SQ(mData[i]);
		return result;
	}

	/// @brief Returns a normalized vector.
	/// @return A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector Normalized() const
	{
		float norm = Norm();
		if (norm == 0)
			return 0;

		__assume(norm != 0.f);
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] / norm;
		return result;
	}

	/// @brief Returns the dot product of this Vector with 'other'.
	[[nodiscard]]
	float Dot(const Vector<M>& other) const
	{
		float result = 0;
		for (size_t i = 0; i < M; i++)
			result += mData[i] * other[i];
		return result;
	}

	/// @brief Returns the cross product of this Vector with 'other'.
	[[nodiscard]]
	Vector<M> Cross(const Vector<M>& other) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[(i + 1) % M] * other[(i + 2) % M] - mData[(i + 2) % M] * other[(i + 1) % M];
		return result;
	}

    /// @brief Returns a Vector2 representing the size of this matrix. This operation
    ///        casts two size_t to floats and therefore might be inaccurate if used
    ///        with huge numbers.
    [[nodiscard]]
    constexpr size_t Size() const { return M; }

	/// @brief Returns a · b.
	[[nodiscard]]
	static float Dot(const Vector<M>& a, const Vector<M>& b)
	{
		return a.Dot(b);
	}

	/// @brief Returns a x b.
	[[nodiscard]]
	static Vector<M> Cross(const Vector<M>& a, const Vector<M>& b)
	{
		return a.Cross(b);
	}
#pragma endregion

#pragma region operators
	[[nodiscard]]
	float operator[](const size_t i) const
	{
		return mData[i];
	}

	[[nodiscard]]
	float& operator[](const size_t i)
	{
		return mData[i];
	}

    /// @brief Sets the first element of the vector to the given value.
    Vector& operator=(const float value)
	{
		mData[0] = value;
		return *this;
	}

    explicit operator Vector2() const
	{
		assert(M >= 2 && "Vector must be at least of size 2 for a cast to Vector2");
		__assume(M >= 2);

		return Vector2(mData[0], mData[1]);
	}

    explicit operator Vector3() const
	{
		assert(M >= 3 && "Vector must be at least of size 3 for a cast to Vector3");
		__assume(M >= 3);

		return Vector3(mData[0], mData[1], mData[2]);
	}

	[[nodiscard]]
	Vector<M> operator+(const Vector<M>& other) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] + other[i];
		return result;
	}

	[[nodiscard]]
	Vector<M> operator-(const Vector<M>& other) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] - other[i];
		return result;
	}

	[[nodiscard]]
	Vector<M> operator-() const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = -mData[i];
		return result;
	}

	[[nodiscard]]
	Vector<M> operator*(const Vector<M>& other) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] * other[i];
		return result;
	}

	[[nodiscard]]
	Vector<M> operator*(const float factor) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] * factor;
		return result;
	}

	[[nodiscard]]
	Vector<M> operator/(const Vector<M>& other) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] / other[i];
		return result;
	}

	[[nodiscard]]
	Vector<M> operator/(const float factor) const
	{
		Vector<M> result;
		for (size_t i = 0; i < M; i++)
			result[i] = mData[i] / factor;
		return result;
	}

	Vector<M>& operator+=(const Vector<M>& other)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] += other[i];
		return *this;
	}

	Vector<M>& operator+=(const float factor)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] += factor;
		return *this;
	}

	Vector<M>& operator-=(const Vector<M>& other)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] -= other[i];
		return *this;
	}

	Vector<M>& operator-=(const float factor)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] -= factor;
		return *this;
	}

	Vector<M>& operator*=(const Vector<M>& other)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] *= other[i];
		return *this;
	}

	Vector<M>& operator*=(const float factor)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] *= factor;
		return *this;
	}

	Vector<M>& operator/=(const Vector<M>& other)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] /= other[i];
		return *this;
	}

	Vector& operator/=(const float factor)
	{
		for (size_t i = 0; i < M; i++)
			mData[i] /= factor;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector<M>& v)
	{
		out << "[ ";
		for (size_t i = 0; i < M; i++)
		{
			char buffer[10] = {};
			sprintf_s(buffer, sizeof(buffer), "%6.3f", v.mData[i]);
			out << buffer;
			if (i != M - 1)
				out << ", ";
			else
				out << " ";
		}
		return out << "]";
	}
#pragma endregion

private:
    float mData[M];
};

#undef SQ
