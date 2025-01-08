#pragma once

#include "Mountain/game.hpp"

class MzmGame : public Mountain::Game
{
public:
    MzmGame();

private:
    void Initialize() override;
    void LoadResources() override;
    void Update() override;
    void Render() override;
    void Shutdown() override;
};
