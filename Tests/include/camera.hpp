#pragma once

#include <Maths/matrix.hpp>

class Camera
{
public:
    Camera() = default;

    Vector2 position;
    float_t rotation; // Rotation in degrees
    float scale = 1.f;

    [[nodiscard]]
    Vector2 ToWorld(Vector2 value) const;
    [[nodiscard]]
    Vector2 ToScreen(Vector2 value) const;

    void UpdateMatrix();

private:
    Matrix matrix = Matrix::Identity();
    Matrix invMatrix = Matrix::Identity();
};
