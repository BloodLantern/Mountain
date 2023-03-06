#pragma once

#include <vector>

#include "entity.hpp"
#include "renderer.hpp"

namespace mountain
{
    class Game
    {
    public:
        Game();
        ~Game();

        virtual void Initialize() {}
        void MainLoop();
        virtual void Shutdown() {}

        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        std::vector<Entity> mEntities;
        Renderer mRenderer;
        double mDeltaTime = 0.0;
    };
}
