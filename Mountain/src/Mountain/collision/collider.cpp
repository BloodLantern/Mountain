#include "Mountain/collision/collider.hpp"

#include "Mountain/scene/entity.hpp"

Mountain::Collider::Collider(const ColliderType type)
    : type(type)
{
}

Mountain::Collider::Collider(const ColliderType type, const Vector2& position)
    : position(position)
    , type(type)
{
}

bool_t Mountain::Collider::CheckCollision(const Entity& e) const { return CheckCollision(*e.GetCollider()); }

bool_t Mountain::Collider::CheckCollision(const Collider& collider) const
{
    switch (collider.type)
    {
        case ColliderType::Hitbox:
            return CheckCollision(reinterpret_cast<const Hitbox&>(collider));
        case ColliderType::Circle:
            return CheckCollision(reinterpret_cast<const Circle&>(collider));
        case ColliderType::Grid:
            return CheckCollision(reinterpret_cast<const Grid&>(collider));
        case ColliderType::List:
            return CheckCollision(reinterpret_cast<const ColliderList&>(collider));
        case ColliderType::Count:
            throw std::runtime_error("Invalid collider type");
    }
    
    throw std::runtime_error("Invalid collider type");
}

float_t Mountain::Collider::Width() const { return Right() - Left(); }

float_t Mountain::Collider::Height() const { return Bottom() - Top(); }

Vector2 Mountain::Collider::Size() const { return Vector2(Width(), Height()); }

Vector2 Mountain::Collider::Center() const { return Vector2(Left() + Width() / 2, Top() + Height() / 2); }

const Mountain::Entity* Mountain::Collider::GetEntity() const { return m_Entity; }

Mountain::Entity* Mountain::Collider::GetEntity() { return m_Entity; }
