#pragma once

#include <vector>

#include "collider.hpp"
#include "entity.hpp"

namespace mountain
{
    typedef void (*ColliderHitCallback)(Entity& entity, Entity& other);

    class Collide
    {
    public:
        Collide() = delete;

        /// @brief Check if the lines (p1, p1 + p2) and (p3, p3 + p4) collide.
        /// @return A std::pair where the first element is true if the lines intersect,
        ///         and the second element is the position of the collision.
        static std::pair<bool, Vector2> LinesIntersect(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4);
        
        static bool CheckCollision(const Collider& a, const Collider& b) { return a.CheckCollision(b); }
        static bool CheckCollision(const Entity& a, const Entity& b) { return CheckCollision(*a.Collider, *b.Collider); }

        static void CheckCollisions(const std::vector<const Collider*>& colliders, ColliderHitCallback callback);
    };
}
