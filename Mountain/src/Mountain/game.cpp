#include "Mountain/game.hpp"

#include "Mountain/window.hpp"
#include "Mountain/audio/audio.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/coroutine.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

Game::Game(const std::string_view windowTitle, const Vector2i windowSize, const bool_t vsync)
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
        Logger::LogError("Failed to initialize audio {}", windowSize);
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
    // Start the time now
    Time::Initialize();
    
    Window::SetVisible(true);
    
    while (!Window::GetShouldClose())
    {
        Window::PollEvents();
        
        Time::Update();
        Input::Update();
        Audio::Update();
        
        Renderer::PreFrame();
            
        if (Time::freezeTimer <= 0.f)
            Update();
        Render();

        Renderer::PostFrame();
        Window::SwapBuffers();
        
        Coroutine::UpdateAll();
		Input::Reset();
    }

	Coroutine::StopAll();
}

void Game::Shutdown()
{
}
