#include "game.hpp"

#include "renderer.hpp"

mountain::Game::Game(const char* const windowTitle, const int windowWidth, const int windowHeight)
{
    Renderer::Initialize(windowTitle, windowWidth, windowHeight);
}

mountain::Game::~Game()
{
    Renderer::Shutdown();
}

void mountain::Game::MainLoop()
{
    while (!glfwWindowShouldClose(Renderer::GetWindow()))
    {
        double t = glfwGetTime();

        Renderer::PreFrame();
        PreRender();

        // Call game loop
        Update();
        Render();

        PostRender();
        Renderer::PostFrame();

        DeltaTime = (float) (glfwGetTime() - t);
    }
}
