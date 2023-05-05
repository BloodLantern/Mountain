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

        if (RenderEachFrame)
        {
            Renderer::PreFrame();
            PreRender();
        }
        else
            glfwPollEvents();

        if (UpdateInputsEachFrame)
            Input::Update();
            
        if (UpdateEachFrame && FreezeTimer <= 0)
            Update();
        if (RenderEachFrame)
        {
            Render();

            PostRender();
            Renderer::PostFrame();
        }
        else
            glfwSwapBuffers(Renderer::GetWindow());

        FreezeTimer -= DeltaTime;
        DeltaTime = (float) (glfwGetTime() - t) * TimeScale;
    }
}

void mountain::Game::Redraw()
{
    if (RenderEachFrame)
        return;

    Renderer::PreFrame();
    PreRender();

    Render();

    PostRender();
    Renderer::PostFrame();
}
