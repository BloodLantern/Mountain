
#include "Mountain/Math/Matrix2.hpp"

#include <iostream>

Matrix2 Matrix2::RotationZ(const f32 angle) noexcept
{
    return RotationZ(std::cos(angle), std::sin(angle));
}

void Matrix2::RotationZ(const f32 angle, Matrix2* result) noexcept
{
    RotationZ(std::cos(angle), std::sin(angle), result);
}

void Matrix2::DebugPrint() const noexcept
{
    std::cout << "{ "
        << m00 << ' ' << m10 << " }\n{ "
        << m01 << ' ' << m11 << " }\n";
}

Matrix2::operator Matrix3() const
{
    return Matrix3(
        m00, m01, 0.f,
        m10, m11, 0.f,
        0.f, 0.f, 1.f
    );
}

Matrix2::operator Matrix() const
{
    return Matrix(
        m00, m01, 0.f, 0.f,
        m10, m11, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}
