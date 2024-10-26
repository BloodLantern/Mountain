#pragma once

#include <Mountain/scene/entity.hpp>

#include "ball.hpp"

constexpr Vector2 PlayerSize{ 100.f, 20.f };
constexpr float_t PlayerMovementSpeed = 50.f;

class Paddle : public Mountain::Entity
{
public:
    explicit Paddle(Ball& ball);
    ~Paddle() override;

    DEFAULT_COPY_MOVE_OPERATIONS(Paddle)
    
    void Update() override;
    void Render() override;
    void RenderDebug() override;
    void RenderImGui();

private:
    Ball* m_Ball = nullptr;

    void CheckBallCollisions() const;
};
