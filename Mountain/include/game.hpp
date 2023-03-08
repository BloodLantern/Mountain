#pragma once

#include <vector>

#include "entity.hpp"
#include "renderer.hpp"

namespace mountain
{
    class Game
    {
    public:
        Game(const char* const windowTitle, const int windowWidth = 1280, const int windowHeight = 720);
        ~Game();

        virtual void Initialize() {}
        void MainLoop();
        virtual void Shutdown() {}

        virtual void Update() = 0;
        virtual void Render() = 0;

        Renderer GetRenderer() const { return mRenderer; }
        Renderer& GetRenderer() { return mRenderer; }
        std::vector<Entity*> GetEntities() const { return mEntities; }
        std::vector<Entity*>& GetEntities() { return mEntities; }
        float GetDeltaTime() const { return mDeltaTime; }

    protected:
        std::vector<Entity*> mEntities;
        Renderer mRenderer;
        float mDeltaTime = 0.f;
    };
}
