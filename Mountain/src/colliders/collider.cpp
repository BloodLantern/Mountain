#include "colliders/collider.hpp"

#include <cassert>

#include "colliders/hitbox.hpp"
#include "colliders/circle.hpp"

namespace mountain
{
    Collider::Collider(const Vector2& position)
        : mPosition(position)
    {
    }

    bool Collider::CheckCollision(const Collider& collider) const
    {
        assert(collider.mType != ColliderType::NONE && "Invalid collider type in collision check.");

        switch(collider.mType)
        {
            case ColliderType::HITBOX:
                return CheckCollision(dynamic_cast<const Hitbox&>(collider));
            case ColliderType::CIRCLE:
                return CheckCollision(dynamic_cast<const Circle&>(collider));
            default:
                throw std::runtime_error("Invalid collider type in collision check.");
        }
    }
}
