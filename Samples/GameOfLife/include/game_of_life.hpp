#pragma once

#include "camera.hpp"
#include "grid.hpp"
#include "Mountain/game.hpp"
#include "Mountain/rendering/render_target.hpp"

class GameOfLife : public Mountain::Game
{
public:
    explicit GameOfLife(const char_t* title);

    void Initialize() override;
    void Update() override;
    void Render() override;
    void Shutdown() override;

private:
    Grid m_Grid;
    Camera m_Camera;
    Mountain::RenderTarget m_RenderTarget;

    bool_t m_AutoUpdate = false;
    bool_t m_ManualUpdate = false;
    float_t m_UpdateInterval = 0.25f;
};
