#pragma once

#include <Mountain/scene/entity.hpp>

/// @brief Radius of the balls
constexpr float_t BallRadius = 10.f;
constexpr float_t BallMovementSpeed = 400.f;

class Ball : public Mountain::Entity
{
public:
    Vector2 velocity;

    Ball();
    ~Ball() override;

    DEFAULT_COPY_MOVE_OPERATIONS(Ball)
    
    void Update() override;
    void Render() override;
    void RenderDebug() override;
};
