#pragma once

#include <Math/matrix.hpp>

// TODO - Add Camera utility functions

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
