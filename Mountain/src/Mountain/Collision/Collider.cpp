module Mountain:Collision_Collider;
import :Collision_Collider;

import :Ecs_Entity;

Mountain::Collider::Collider(const ColliderType type)
    : type(type)
{
}

Mountain::Collider::Collider(const ColliderType type, const Vector2 offset)
    : offset(offset)
    , type(type)
{
}

Vector2 Mountain::Collider::GetActualPosition() const { return basePosition ? *basePosition + offset : offset; }

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
    }

    throw std::runtime_error("Invalid collider type");
}

Vector2 Mountain::Collider::Center() const { return offset + Size() * 0.5f; }

Vector2 Mountain::Collider::TopLeft() const { return { Left(), Top() }; }

Vector2 Mountain::Collider::TopRight() const { return { Right(), Top() }; }

Vector2 Mountain::Collider::BottomLeft() const { return { Left(), Bottom() }; }

Vector2 Mountain::Collider::BottomRight() const { return { Right(), Bottom() }; }

Vector2 Mountain::Collider::AbsoluteCenter() const { return GetActualPosition() + Size() * 0.5f; }

Vector2 Mountain::Collider::AbsoluteTopLeft() const { return { AbsoluteLeft(), AbsoluteTop() }; }

Vector2 Mountain::Collider::AbsoluteTopRight() const { return { AbsoluteRight(), AbsoluteTop() }; }

Vector2 Mountain::Collider::AbsoluteBottomLeft() const { return { AbsoluteLeft(), AbsoluteBottom() }; }

Vector2 Mountain::Collider::AbsoluteBottomRight() const { return { AbsoluteRight(), AbsoluteBottom() }; }

float_t Mountain::Collider::Width() const { return AbsoluteRight() - AbsoluteLeft(); }

float_t Mountain::Collider::Height() const { return AbsoluteBottom() - AbsoluteTop(); }

Vector2 Mountain::Collider::Size() const { return { Width(), Height() }; }
