#include "collider.hpp"

#include <cassert>

#include "hitbox.hpp"
#include "circle.hpp"
#include "grid.hpp"

mountain::Collider::Collider(const Vector2& position)
    : Position(position)
{
}

bool mountain::Collider::CheckCollision(const Collider& collider) const
{
    assert(collider.Type != ColliderType::NONE && "Invalid collider type in collision check.");

    switch(collider.Type)
    {
        case ColliderType::HITBOX:
            return CheckCollision(dynamic_cast<const Hitbox&>(collider));
        case ColliderType::CIRCLE:
            return CheckCollision(dynamic_cast<const Circle&>(collider));
        case ColliderType::GRID:
            return CheckCollision(dynamic_cast<const Grid&>(collider));
        default:
            throw std::runtime_error("Invalid collider type in collision check.");
    }
}
