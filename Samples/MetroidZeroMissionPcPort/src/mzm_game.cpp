#include "mzm_game.hpp"

#include "Mountain/rendering/draw.hpp"

MzmGame::MzmGame()
    : Game("Metroid: Zero Mission (PC Port)")
{
}

void MzmGame::Initialize()
{
    Game::Initialize();
}

void MzmGame::LoadResources()
{
}

void MzmGame::Update()
{
}

void MzmGame::Render()
{
    Mountain::Draw::Clear(Mountain::Color::CornflowerBlue());
}

void MzmGame::Shutdown()
{
    Game::Shutdown();
}
