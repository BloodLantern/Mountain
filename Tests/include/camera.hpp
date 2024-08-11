#pragma once

#include <Maths/matrix.hpp>

class Camera
{
public:
    Camera() = default;

    Vector2 position;
    float_t rotation;
    Vector2 scale = Vector2::One();

    void UpdateMatrix();

    Matrix matrix = Matrix::Identity();
};
