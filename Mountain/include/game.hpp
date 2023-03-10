#pragma once

#include <vector>

#include "entity.hpp"
#include "renderer.hpp"

namespace mountain
{
    class Game
    {
    public:
        std::vector<Entity*> Entities;
        Renderer Renderer;
        float DeltaTime = 0.f;

        Game(const char* const windowTitle, const int windowWidth = 1280, const int windowHeight = 720);
        ~Game();

        virtual void Initialize() {}
        void MainLoop();
        virtual void Shutdown() {}

        virtual void PreRender() {}
        virtual void PostRender() {}

        virtual void Update() = 0;
        virtual void Render() = 0;
    };
}
