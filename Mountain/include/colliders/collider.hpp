#pragma once

#include <vector2.hpp>

#include "entity.hpp"
#include "color.hpp"

namespace mountain
{
    enum class ColliderType : unsigned char
    {
        None,
        Hitbox,
        Circle,
        Grid
    };

    // Colliders forward declarations
    class Hitbox;
    class Circle;
    class Grid;

    class Collider
    {
    public:
        Vector2 Position;
        Entity* Owner = nullptr;
        ColliderType Type = ColliderType::None;

        Collider() {};
        Collider(const Vector2& position);
        virtual ~Collider() {}

        virtual void Draw(const Color color) const = 0;

        bool CheckCollision(const Entity& entity) const { return CheckCollision(*entity.Collider); }
        bool CheckCollision(const Collider& collider) const;
        virtual bool CheckCollision(const Vector2& point) const = 0;
        virtual bool CheckCollision(const Hitbox& hitbox) const = 0;
        virtual bool CheckCollision(const Circle& circle) const = 0;
        virtual bool CheckCollision(const Grid& grid) const = 0;

        virtual inline float Left() const = 0;
        virtual inline float Right() const = 0;
        virtual inline float Top() const = 0;
        virtual inline float Bottom() const = 0;
        virtual inline Vector2 Center() const = 0;
        virtual inline float Width() const { return Right() - Left(); }
        virtual inline float Height() const { return Bottom() - Top(); }
        virtual inline Vector2 Size() const { return Vector2(Width(), Height()); }
    };
}
