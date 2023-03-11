#pragma once

#include <vector>

#include "entity.hpp"

namespace mountain
{
    class Game
    {
    public:
        float DeltaTime = 0.f;

        Game(const char* const windowTitle, const int windowWidth = 1280, const int windowHeight = 720);
        ~Game();

        /// @brief To be called by the user when starting execution. Empty by default,
        ///        can be overriden to initialize custom variables or fields.
        virtual void Initialize() {}
        /// @brief Called once. Runs until the window is closed and calls all the
        ///        necessary functions of the game.
        void MainLoop();
        /// @brief To be called by the user when closing the window. Empty by default,
        ///        can be overriden to destroy custom variables or fields.
        virtual void Shutdown() {}

        /// @brief Automatically called once at the beginning of each frame. Empty by
        ///        default, can be overriden.
        virtual void PreRender() {}
        /// @brief Automatically called once at the end of each frame. Empty by default,
        ///        can be overriden.
        virtual void PostRender() {}

        /// @brief Called once each frame before Game::Render. To be overriden by the user.
        virtual void Update() = 0;
        /// @brief Called once each frame after Game::Update. To be overriden by the user.
        virtual void Render() = 0;
    };
}
