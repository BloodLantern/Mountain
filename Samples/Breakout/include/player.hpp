#pragma once

#include <Mountain/scene/entity.hpp>

#include "ball.hpp"

constexpr Vector2 PlayerSize{ 100.f, 20.f };
constexpr float_t PlayerMovementSpeed = 50.f;

class Player : public Mountain::Entity
{
public:
    explicit Player(Ball& ball);
    ~Player() override;

    DEFAULT_COPY_MOVE_OPERATIONS(Player)
    
    void Update() override;
    void Render() override;
    void RenderDebug() override;
    void RenderImGui();

private:
    Ball* ball = nullptr;
};
