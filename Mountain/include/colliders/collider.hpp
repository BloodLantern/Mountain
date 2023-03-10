#pragma once

#include <vector2.hpp>

#include "entity.hpp"
#include "color.hpp"

namespace mountain
{
    enum class ColliderType : unsigned char
    {
        NONE,
        HITBOX,
        CIRCLE
    };

    // Colliders forward declarations
    class Hitbox;
    class Circle;

    class Collider
    {
    public:
        Vector2 Position;
        Entity* Owner = nullptr;
        ColliderType Type = ColliderType::NONE;

        Collider() {};
        Collider(const Vector2& position);
        virtual ~Collider() {}

        virtual void Draw(Color color) const = 0;

        bool CheckCollision(const Entity& entity) const { return CheckCollision(*entity.Collider); };
        bool CheckCollision(const Collider& collider) const;
        virtual bool CheckCollision(const Vector2& point) const = 0;
        virtual bool CheckCollision(const Hitbox& hitbox) const = 0;
        virtual bool CheckCollision(const Circle& circle) const = 0;

        virtual inline float Left() const = 0;
        virtual inline float Right() const = 0;
        virtual inline float Top() const = 0;
        virtual inline float Bottom() const = 0;
        virtual inline Vector2 Center() const = 0;
    };
}
