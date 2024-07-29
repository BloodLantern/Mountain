#include "game.hpp"

#include "coroutine.hpp"
#include "window.hpp"
#include "audio/audio.hpp"
#include "input/input.hpp"
#include "input/time.hpp"
#include "rendering/renderer.hpp"
#include "resource/resource_manager.hpp"
#include "utils/logger.hpp"

using namespace Mountain;

Game::Game(const char_t* const windowTitle, const Vector2i windowSize, const bool_t vsync)
{
    Logger::Start();
    Logger::OpenDefaultFile();
    
    Logger::LogInfo("Initializing Mountain Framework");
    
    if (!Renderer::Initialize(windowTitle, windowSize, vsync))
    {
        Logger::LogFatal("Failed to initialize renderer, shutting down");
        throw std::runtime_error("Failed to initialize renderer");
    }
    
    if (!Audio::Initialize())
        Logger::LogError("Failed to initialize audio");
}

Game::~Game()
{
    Logger::LogInfo("Shutting down Mountain Framework...");
    
    ResourceManager::UnloadAll();
    FileManager::UnloadAll();
    
    Audio::Shutdown();
    Renderer::Shutdown();
    
    Logger::Stop();
}

void Game::Play()
{
    Initialize();
    LoadResources();
    MainLoop();
    Shutdown();
}

void Game::Initialize()
{
}

void Game::LoadResources()
{
}

void Game::MainLoop()
{
    Window::SetVisible(true);
    
    while (!Window::ShouldClose())
    {
        Window::PollEvents();
        
        Time::Update();
        Input::Update();
        Audio::Update();
        
        Renderer::PreFrame();
            
        if (freezeTimer <= 0)
            Update();
        Render();

        Renderer::PostFrame();
        Window::SwapBuffers();
        
        Coroutine::UpdateAll();
		Input::Reset();

        freezeTimer -= Time::GetDeltaTime();
    }

	Coroutine::StopAll();
}

void Game::Shutdown()
{
}
