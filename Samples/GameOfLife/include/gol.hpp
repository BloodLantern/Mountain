#pragma once

#include "Mountain/game.hpp"

class Gol : public Mountain::Game
{
public:
    explicit Gol(const char_t* title);

    void Initialize() override;
    void Update() override;
    void Render() override;
    void Shutdown() override;
};
