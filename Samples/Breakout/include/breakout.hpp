#pragma once

#include <Mountain/game.hpp>

#include "ball.hpp"
#include "block.hpp"
#include "paddle.hpp"

class Breakout : public Mountain::Game
{
public:
    Breakout();

private:
    Paddle m_Paddle;
    Ball m_Ball;
    Mountain::List<Block*> m_Blocks;
    bool_t m_ShowHitboxes = false;
    
    void Initialize() override;
    void Shutdown() override;
    void Update() override;
    void Render() override;
    void RenderImGui();
};
