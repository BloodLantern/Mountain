#pragma once

#include <Mountain/game.hpp>

#include "ball.hpp"
#include "block.hpp"
#include "player.hpp"

class Breakout : public Mountain::Game
{
public:
    Breakout();

private:
    Player m_Player;
    Ball m_Ball;
    Mountain::List<Block*> m_Blocks;
    bool_t m_ShowHitboxes = false;
    
    void Initialize() override;
    void Shutdown() override;
    void Update() override;
    void Render() override;
    void RenderImGui();
};
