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

using namespace Mountain;

Game::Game(const std::string& windowTitle, const Vector2i windowSize)
{
    Logger::Start();
    Logger::OpenDefaultFile();

    std::set_terminate(
        []
        {
            Logger::LogWarning("std::terminate called");

            try
            {
                const std::exception_ptr exceptionPtr = std::current_exception();
                if (exceptionPtr)
                    std::rethrow_exception(exceptionPtr);

                Logger::LogInfo("Exiting without exception");
                Logger::Stop();
            }
            catch (const std::exception& e)
            {
                const char_t* const t = typeid(e).name();
                Logger::LogFatal("Uncaught exception of type {}: {}", t, e);
                Logger::Stop();
                MessageBox::Show(std::format("Unhandled exception of type {}", t), std::format("{}", e), MessageBox::Type::Ok, MessageBox::Icon::Error);
            }

#ifdef _DEBUG
            std::abort();
#else
            std::exit(-1);
#endif
        }
    );

    Logger::LogInfo("Initializing Mountain Framework");

    if (!Renderer::Initialize(windowTitle, windowSize))
        throw std::runtime_error("Failed to initialize renderer");

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
    MainLoop();
    Shutdown();
}

void Game::Initialize()
{
    LoadResources();

    // Start the time now
    Time::Initialize();

    Window::SetVisible(true);
}

void Game::LoadResources()
{
}

void Game::MainLoop()
{
    while (NextFrame()) {}
}

bool_t Game::NextFrame()
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

    Input::Reset();
    Time::WaitForNextFrame();

    return !Window::GetShouldClose();
}

void Game::Shutdown()
{
	Coroutine::StopAll();
}
