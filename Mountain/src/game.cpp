#include "game.hpp"

#include "renderer.hpp"
#include "input.hpp"

mountain::Game::Game(const char* const windowTitle, const int windowWidth, const int windowHeight, const bool vsync)
{
    Renderer::Initialize(windowTitle, windowWidth, windowHeight, vsync);
    Input::Initialize();
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

        Input::Update();
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
