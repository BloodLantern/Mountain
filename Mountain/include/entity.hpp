#pragma once

#include <vector2.hpp>

namespace mountain
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(const Vector2 position) : mPosition(position) {}
        virtual ~Entity() = default;

        virtual void Update(const double deltaTime) = 0;
        virtual void Draw() = 0;

    protected:
        Vector2 mPosition = 0;
    };
}
