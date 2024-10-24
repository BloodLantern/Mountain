#pragma once

#include <Mountain/game.hpp>

class Breakout : public Mountain::Game
{
public:
    Breakout(const std::string_view& windowTitle, const Vector2i& windowSize, bool_t vsync)
        : Game(windowTitle, windowSize, vsync)
    {
    }

private:
    void Initialize() override;
    void LoadResources() override;
    void Shutdown() override;
    void Update() override;
    void Render() override;
};
