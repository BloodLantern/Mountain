
#include "Mountain/Math/Vector3.hpp"

#include <cassert>
#include <format>

#include "Mountain/Math/Calc.hpp"
#include "Mountain/Math/Matrix.hpp"
#include "Mountain/Math/Vector2.hpp"
#include "Mountain/Math/Vector4.hpp"

f32 Vector3::Length() const noexcept
{
	return std::sqrt(SquaredLength());
}

Vector3::operator Vector4() const noexcept
{
    return Vector4(x, y, z, 1.f);
}

Vector3 Vector3::Normalized() const noexcept
{
	const f32 length = Length();
	if (Calc::IsZero(length))
		return Zero();

	__assume(length != 0.f);
	const f32 invLength = 1.f / length;
	return Vector3(x * invLength, y * invLength, z * invLength);
}

void Vector3::Normalized(Vector3* result) const noexcept
{
	const f32 length = Length();
	if (Calc::IsZero(length))
	{
		*result = Zero();
		return;
	}

	__assume(length != 0.f);
	const f32 invLength = 1.f / length;
	*result = Vector3(x * invLength, y * invLength, z * invLength);
}

bool Vector3::IsInfinity() const noexcept
{
	return std::isinf(x)
		&& std::isinf(y)
		&& std::isinf(z);
}

bool Vector3::IsNaN() const noexcept
{
	return std::isnan(x)
		&& std::isnan(y)
		&& std::isnan(z);
}

Vector3::operator Vector2() const noexcept
{
	return Vector2(x, y);
}

Vector3 Vector3::Rescaled(const f32 newLength) const noexcept
{
    return *this * newLength / Length();
}

std::ostream& operator<<(std::ostream& out, const Vector3& v) noexcept
{
	return out << std::format("{{{:.3f} {:.3f} {:.3f}}}", v.x, v.y, v.z);
}
