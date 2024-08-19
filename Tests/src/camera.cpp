#include "camera.hpp"

void Camera::UpdateMatrix()
{
    matrix = Matrix::Trs(static_cast<Vector3>(-position), rotation * Vector3::UnitZ(), Vector3(scale.x, scale.y, 1.f));
}
