#include "game.hpp"

mountain::Game::Game()
{
    mRenderer.Initialize();
}

mountain::Game::~Game()
{
    mRenderer.Shutdown();
}

void mountain::Game::MainLoop()
{
    while (!glfwWindowShouldClose(mRenderer.GetWindow()))
    {
        double t = glfwGetTime();

        mRenderer.PreFrame();

        // Call game loop
        Update();
        Render();

        mRenderer.PostFrame();

        mDeltaTime = (float) (glfwGetTime() - t);
    }
}
