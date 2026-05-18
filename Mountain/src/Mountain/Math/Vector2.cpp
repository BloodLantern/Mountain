#include "Mountain/Math/Vector2.hpp"

#include <format>

#include "Mountain/Math/Calc.hpp"
#include "Mountain/Math/Vector2i.hpp"
#include "Mountain/Math/Vector3.hpp"
#include "Mountain/Math/Vector4.hpp"

f32 Vector2::Length() const noexcept
{
	return std::sqrt(SquaredLength());
}

Vector2 Vector2::Rescaled(const f32 newLength) const noexcept
{
    return *this * newLength / Length();
}

Vector2 Vector2::Normalized() const noexcept
{
	const f32 length = Length();
	if (Calc::IsZero(length))
		return Zero();

    ASSUME(length != 0.f);
	const f32 invLength = 1.f / length;
	return Vector2(x * invLength, y * invLength);
}

Vector2 Vector2::Normal() const noexcept { return Vector2(y, -x).Normalized(); }

Vector2 Vector2::Rotated(const f32 angle) const noexcept { return Rotated(std::cos(angle), std::sin(angle)); }

Vector2 Vector2::Rotated(const f32 c, const f32 s) const noexcept { return Vector2(x * c - y * s, x * s + y * c); }

f32 Vector2::GetAngle() const noexcept
{
	return std::atan2(y, x);
}

bool Vector2::IsInfinity() const noexcept
{
	return std::isinf(x)
		&& std::isinf(y);
}

bool Vector2::IsNaN() const noexcept
{
	return std::isnan(x)
		&& std::isnan(y);
}

Vector2::operator Vector2i() const noexcept
{
	return Vector2i(static_cast<s32>(std::round(x)), static_cast<s32>(std::round(y)));
}

Vector2::operator Vector3() const noexcept
{
	return Vector3(x, y, 0.f);
}

Vector2::operator Vector4() const noexcept
{
	return Vector4(x, y, 0.f, 1.f);
}

std::ostream& operator<<(std::ostream& out, const Vector2 v) noexcept
{
	return out << std::format("{{{:.3f} {:.3f}}}", v.x, v.y);
}
