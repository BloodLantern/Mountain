
#include "Mountain/Math/Vector2i.hpp"

#include <format>

#include "Mountain/Math/Calc.hpp"
#include "Mountain/Math/Vector2.hpp"
#include "Mountain/Math/Vector3.hpp"
#include "Mountain/Math/Vector4.hpp"

float Vector2i::Length() const noexcept
{
	return std::sqrt(SquaredLength());
}

Vector2 Vector2i::Normalized() const
{
	const float length = Length();
	if (Calc::IsZero(length))
		return Vector2::Zero();

    __assume(length != 0.f);
	const float invLength = 1.f / length;
	return Vector2(static_cast<float>(x) * invLength, static_cast<float>(y) * invLength);
}

Vector2 Vector2i::Normal() const
{
	return Vector2i(y, -x).Normalized();
}

Vector2i::operator Vector2() const
{
	return Vector2(static_cast<float>(x), static_cast<float>(y));
}

Vector2i::operator Vector3() const
{
	return Vector3(static_cast<float>(x), static_cast<float>(y), 0.f);
}

Vector2i::operator Vector4() const
{
	return Vector4(static_cast<float>(x), static_cast<float>(y), 0.f, 0.f);
}

std::ostream& operator<<(std::ostream& out, const Vector2i v) noexcept
{
	return out << std::format("{{{:d} {:d}}}", v.x, v.y);
}
