#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Game.hpp"

#include "Mountain/Window.hpp"
#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Graphics/Renderer.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Coroutine.hpp"
#include "Mountain/Utils/Logger.hpp"
#include "Mountain/Utils/MessageBox.hpp"

// ReSharper disable once CppUnusedIncludeDirective
#include "Mountain/Profiler.hpp"

#include "Mountain/Globals.hpp"

using namespace Mountain;

Game::Game(const std::string& windowTitle, const Vector2i windowSize)
{
    TracyNoop; // Make sure Tracy is correctly initialized

    ZoneScoped;

    Logger::Start();
    Logger::OpenDefaultFile();

    std::set_terminate(
        []
        ATTRIBUTE_NORETURN
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
            catch (const Exception& e)
            {
                const char_t* t = e.GetName();
                Logger::LogFatal("Uncaught Mountain exception of type {} occurred at {}: {}", t, e.GetState(), e);
                Logger::Stop();
                MessageBox::Show(std::format("Unhandled exception of type {}", t).c_str(), std::format("{}", e).c_str(), MessageBox::Type::Ok, MessageBox::Icon::Error);
            }
            catch (const std::exception& e)
            {
                const char_t* t = typeid(e).name();
                Logger::LogFatal("Uncaught std exception of type {}: {}", t, e);
                Logger::Stop();
                MessageBox::Show(std::format("Unhandled exception of type {}", t).c_str(), std::format("{}", e).c_str(), MessageBox::Type::Ok, MessageBox::Icon::Error);
            }

#ifdef _DEBUG
            std::abort();
#else
            std::exit(-1);  // NOLINT(concurrency-mt-unsafe)
#endif
        }
    );

    Logger::LogInfo("Initializing Mountain Framework");

    if (!Renderer::Initialize(windowTitle, windowSize))
        THROW(InvalidOperationException{"Failed to initialize renderer"});

    if (!Audio::Initialize())
        Logger::LogError("Failed to initialize audio {}", windowSize);
}

Game::~Game()
{
    ZoneScoped;

    Logger::LogInfo("Shutting down Mountain Framework...");

	Coroutine::StopAll();

    ResourceManager::UnloadAll();
    FileManager::UnloadAll();

    Audio::Shutdown();
    Renderer::Shutdown();

    Logger::Stop();
}

void Game::Play()
{
    ZoneScoped;

    LoadResources();
    Initialize();
    MainLoop();
    Shutdown();
}

void Game::MainLoop()
{
    Start();

    while (NextFrame());
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Game::Start()
{
    ZoneScoped;

    // Start the time now
    Time::Initialize();

    Window::SetVisible(true);
}

bool_t Game::NextFrame()
{
    ZoneScoped;

    Window::PollEvents();

    Time::Update();
    Audio::Update();

    if (!ManualCoroutineUpdates)
        Coroutine::UpdateAll();

    Renderer::PreFrame();

    if (ManualFreezeFrames || Time::freezeTimer <= 0.f)
    {
        ZoneScopedN("Game::Update");

        Update();
    }

    if (!Window::GetMinimized())
    {
        ZoneScopedN("Game::Render");

        TracyGpuZone("Game::Render")

        Render();
    }

    Renderer::PostFrame();

    Input::Reset();
    Time::WaitForNextFrame();

    return !Window::shouldClose;
}
