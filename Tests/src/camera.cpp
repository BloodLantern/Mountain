#include "camera.hpp"

Vector2 Camera::ToWorld(const Vector2 value) const
{
    return static_cast<Vector2>(invMatrix * static_cast<Vector3>(value));
}

Vector2 Camera::ToScreen(const Vector2 value) const
{
    return static_cast<Vector2>(matrix * static_cast<Vector3>(value));
}

void Camera::UpdateMatrix()
{
    matrix = Matrix::Trs(static_cast<Vector3>(position), rotation * Calc::Deg2Rad * Vector3::UnitZ(), Vector3(scale, scale, 1.f));
    invMatrix = matrix.Inverted();
}
