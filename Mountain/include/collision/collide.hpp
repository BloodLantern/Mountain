#pragma once

#include "core.hpp"

#include <vector>

#include "collision/collider.hpp"
#include "scene/entity.hpp"

BEGIN_MOUNTAIN

using ColliderHitCallback = void(*)(Entity& entity, Entity& other);

class MOUNTAIN_API Collide
{
    STATIC_CLASS(Collide)
    
public:
    /// @brief Check if the lines (p1, p1 + p2) and (p3, p3 + p4) collide.
    /// @return A std::pair where the first element is true if the lines intersect,
    ///         and the second element is the position of the collision.
    static std::pair<bool, Vector2> LinesIntersect(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4);
    
    static bool CheckCollision(const Collider& a, const Collider& b);
    static bool CheckCollision(const Entity& a, const Entity& b);

    static void CheckCollisions(std::vector<Collider*>& colliders, ColliderHitCallback callback);
};

END_MOUNTAIN
