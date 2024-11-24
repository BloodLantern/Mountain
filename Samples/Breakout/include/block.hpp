#pragma once

#include <Mountain/scene/entity.hpp>

#include "ball.hpp"

constexpr float_t BlockSize = 50.f;

class Block : public Mountain::Entity
{
public:
    explicit Block(Ball& ball);
    ~Block() override;

    DEFAULT_COPY_MOVE_OPERATIONS(Block)
    
    void Update() override;
    void Render() override;
    void RenderDebug() override;

private:
    Ball* m_Ball = nullptr;

    void CheckBallCollisions() const;
};
