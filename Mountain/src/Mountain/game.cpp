#include "Mountain/game.hpp"

#include "Mountain/window.hpp"
#include "Mountain/audio/audio.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/coroutine.hpp"
#include "Mountain/utils/logger.hpp"
#include "Mountain/utils/message_box.hpp"

#ifdef _DEBUG
#define EXECUTE_SAFE(function)                                                                                                                              \
    try                                                                                                                                                     \
    {                                                                                                                                                       \
        function();                                                                                                                                         \
    }                                                                                                                                                       \
    catch (const std::exception& e)                                                                                                                         \
    {                                                                                                                                                       \
        Logger::LogFatal("Uncaught exception in Game::" STRINGIFY(function) "(): {}", e);                                                                   \
        Logger::Stop();                                                                                                                                     \
        MessageBox::Show("Unhandled exception in Game::" STRINGIFY(function) "()", std::format("{}", e), MessageBox::Type::Ok, MessageBox::Icon::Error);    \
        std::terminate();                                                                                                                                   \
    }
#else
#define EXECUTE_SAFE(function)                                                                                                                              \
    try                                                                                                                                                     \
    {                                                                                                                                                       \
        function();                                                                                                                                         \
    }                                                                                                                                                       \
    catch (const std::exception& e)                                                                                                                         \
    {                                                                                                                                                       \
        Logger::LogFatal("Uncaught exception in Game::" STRINGIFY(function) "(): {}", e);                                                                   \
        Logger::Stop();                                                                                                                                     \
        MessageBox::Show("Unhandled exception in Game::" STRINGIFY(function) "()", std::format("{}", e), MessageBox::Type::Ok, MessageBox::Icon::Error);    \
        std::exit(-1);                                                                                                                                      \
    }
#endif

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
    EXECUTE_SAFE(Initialize)
    EXECUTE_SAFE(LoadResources)
    EXECUTE_SAFE(MainLoop)
    EXECUTE_SAFE(Shutdown)
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
        Coroutine::UpdateAll();
        
        Renderer::PreFrame();
            
        if (Time::freezeTimer <= 0.f)
            Update();
        if (!Window::GetMinimized())
            Render();

        Renderer::PostFrame();
        Window::SwapBuffers();
        
		Input::Reset();
    }

	Coroutine::StopAll();
}

void Game::Shutdown()
{
}
