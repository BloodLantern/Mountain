#pragma once

#include <vector>

#include "colliders/collider.hpp"
#include "entity.hpp"

namespace mountain
{
    typedef void (*ColliderHitCallback)(Entity& entity, Entity& other);

    class Collide
    {
    public:
        Collide() = delete;
        
        static bool CheckCollision(const Collider& a, const Collider& b) { return a.CheckCollision(b); }
        static bool CheckCollision(const Entity& a, const Entity& b) { return CheckCollision(*a.GetCollider(), *b.GetCollider()); }

        static void CheckCollisions(const std::vector<const Collider*>& colliders, ColliderHitCallback callback);
    };
}
