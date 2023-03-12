#include "game.hpp"

#include "renderer.hpp"
#include "input.hpp"

mountain::Game::Game(const char* const windowTitle, const int windowWidth, const int windowHeight)
{
    Renderer::Initialize(windowTitle, windowWidth, windowHeight);
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

        Renderer::PreFrame();
        PreRender();
        Input::Update();

        // Call game loop
        Update();
        Render();

        PostRender();
        Renderer::PostFrame();

        DeltaTime = (float) (glfwGetTime() - t);
    }
}
