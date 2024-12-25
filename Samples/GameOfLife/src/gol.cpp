#include "gol.hpp"

#include "Mountain/rendering/draw.hpp"

Gol::Gol(const char_t* title)
    : Game(title)
{
}

void Gol::Initialize()
{
    Game::Initialize();
}

void Gol::Update()
{
}

void Gol::Render()
{
    Mountain::Draw::Clear(Mountain::Color::CornflowerBlue());
}

void Gol::Shutdown()
{
    Game::Shutdown();
}
