#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2i.hpp>

namespace Mountain
{
    class MOUNTAIN_API Game
    {
    public:
        explicit Game(std::string_view windowTitle, Vector2i windowSize = { 1280, 720 });
        virtual ~Game();

        DEFAULT_COPY_MOVE_OPERATIONS(Game)

        void Play();

        /// @brief To be called by the user when starting execution. Empty by default,
        ///        can be overridden to initialize custom variables or fields.
        virtual void Initialize();
        /// @brief Called once. Runs until the window is closed and calls all the
        ///        necessary functions of the game.
        void MainLoop();
        bool_t NextFrame();
        /// @brief To be called by the user when closing the window. Empty by default,
        ///        can be overridden to destroy custom variables or fields.
        virtual void Shutdown();

        /// @brief Called once each frame before Game::Render. To be overridden by the user.
        virtual void Update() = 0;
        /// @brief Called once each frame after Game::Update. To be overridden by the user.
        virtual void Render() = 0;

    private:
        virtual void LoadResources();
    };
}
