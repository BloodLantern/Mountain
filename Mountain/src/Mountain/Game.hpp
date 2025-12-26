#pragma once

#include "Graphics/Renderer.hpp"
#include "Mountain/Core.hpp"

namespace Mountain
{
    /// @brief Base class for a Mountain application.
    ///
    /// A Game is the center of a Mountain application, this is where all the main events are called.
    /// A breakdown of these events can be found below.
    ///
    /// The initialization process is the most verbose:
    /// - First, the Game is constructed.
    /// This is where the whole framework is initialized.
    /// The user application can also initialize anything it needs very early in the initialization process
    /// in its @c Game constructor implementation.
    /// - Then, the @c LoadResources() pure function gets called.
    /// This is where all the necessary user resources should be loaded using the @c FileManager and
    /// @c ResourceManager static classes.
    /// - Then, the @c Initialize() pure function is called.
    /// The user application can initialize anything that needs the previously loaded resources using that
    /// function.
    ///
    /// At this point, the initialization process is over. The next event to get called is the @c MainLoop().
    /// This is a framework-only function that repetitively calls @c Update() and @c Render().
    ///
    /// Once the application lifetime reaches its end (by either closing the main window or using
    /// @c Window::SetShouldClose()), @c Shutdown() gets called. This is where the user application can
    /// clean up everything it needs before closing.
    /// The last thing that happens is the @c Game destructor in which the framework cleans up.
    class Game
    {
    public:
        explicit inline Game(const std::string& windowTitle, Vector2i windowSize = { 1280, 720 });
        MOUNTAIN_API virtual ~Game();

        DEFAULT_COPY_MOVE_OPERATIONS(Game)

        /// @brief Handles the whole @c Game lifetime.
        /// @details Equivalent to calling @c LoadResources(), @c Initialize(), @c MainLoop(), and @c Shutdown().
        MOUNTAIN_API void Play();

        /// @brief Used to load any necessary @c Resource using the @c FileManager and @c ResourceManager
        /// static classes.
        virtual void LoadResources() = 0;

        /// @brief Used to initialize anything that needs the resources to be loaded.
        virtual void Initialize() = 0;

        /// @brief Called once. Runs until the window is closed and calls all the
        /// necessary functions of the game.
        MOUNTAIN_API void MainLoop();

        /// @brief Called once before the first @c NextFrame() call.
        MOUNTAIN_API void Start();

        /// @brief Runs a single frame. Automatically called in @c MainLoop().
        MOUNTAIN_API bool NextFrame();

        /// @brief Used to clean everything up before the application closes.
        virtual void Shutdown() = 0;

        /// @brief Called each frame once before @c Render(). Used to update game logic before rendering.
        virtual void Update() = 0;

        /// @brief Called each frame once after @c Update(). Used to render the current state of the game.
        virtual void Render() = 0;

    private:
        MOUNTAIN_API static void InitializeInternal(const std::string& windowTitle, Vector2i windowSize);
    };
}

// Start of Game.inl

namespace Mountain
{
    inline Game::Game(const std::string& windowTitle, const Vector2i windowSize)
    {
        InitializeInternal(windowTitle, windowSize);

        // By inlining the constructor, we force these functions to be called from the client application,
        // which in turn sets the client's ImGui context to the Mountain shared object one.
        ImGui::SetCurrentContext(Renderer::GetImGuiContext());
    }
}
