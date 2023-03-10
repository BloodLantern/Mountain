#pragma once

#include <vector2.hpp>

namespace mountain
{
    class Collider;

    class Entity
    {
    public:
        Vector2 Position = 0;
        Collider* Collider = nullptr;

        Entity(const Vector2& position) : Position(position) {}
        virtual ~Entity() {}

        virtual void Update(const float deltaTime) = 0;
        virtual void Draw() = 0;
    };
}
