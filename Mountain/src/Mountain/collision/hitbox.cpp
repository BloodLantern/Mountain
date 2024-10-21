#include "Mountain/collision/hitbox.hpp"

#include "Mountain/collision/circle.hpp"
#include "Mountain/collision/collider_list.hpp"
#include "Mountain/collision/grid.hpp"
#include "Mountain/rendering/draw.hpp"

using namespace Mountain;

Hitbox::Hitbox()
    : Collider(ColliderType::Hitbox)
{
}

Hitbox::Hitbox(const Vector2 off, const Vector2 size)
    : Collider(ColliderType::Hitbox, off)
    , size(size)
{
}

void Hitbox::DebugRender(const Color& color) const
{
    Draw::Rectangle(GetActualPosition(), size, color);
}

bool Hitbox::Intersects(const Hitbox &other) const
{
    // Check for a collision with any of the hitbox's corners
    return CheckCollision({ other.AbsoluteLeft(), other.AbsoluteTop() })      // Top left
        || CheckCollision({ other.AbsoluteRight(), other.AbsoluteTop() })     // Top right
        || CheckCollision({ other.AbsoluteLeft(), other.AbsoluteBottom() })   // Bottom left
        || CheckCollision({ other.AbsoluteRight(), other.AbsoluteBottom() }); // Bottom right
}

bool Hitbox::CheckCollision(const Vector2 point) const
{
    return point.x < AbsoluteRight() && point.x > AbsoluteLeft()
        && point.y < AbsoluteBottom() && point.y > AbsoluteTop();
}

bool Hitbox::CheckCollision(const Hitbox& hitbox) const
{
    // Check if one of the edges is inside this hitbox
    return hitbox.AbsoluteLeft() < AbsoluteRight() && hitbox.AbsoluteRight() > AbsoluteLeft()
        && hitbox.AbsoluteTop() < AbsoluteBottom() && hitbox.AbsoluteBottom() > AbsoluteTop();
}

bool Hitbox::CheckCollision(const Circle& circle) const
{
    if (CheckCollision(circle.GetActualPosition()))
        return true;

    const Vector2 topLeft{ AbsoluteLeft(), AbsoluteTop() };
    const Vector2 topRight{ AbsoluteRight(), AbsoluteTop() };
    const Vector2 bottomLeft{ AbsoluteLeft(), AbsoluteBottom() };
    const Vector2 bottomRight{ AbsoluteRight(), AbsoluteBottom() };
            
    return circle.Intersect(topLeft, topRight)
        || circle.Intersect(topRight, bottomRight)
        || circle.Intersect(bottomRight, bottomLeft)
        || circle.Intersect(bottomLeft, topLeft);
}

bool Hitbox::CheckCollision(const Grid &grid) const
{
    // Implementation is in 'collision/grid.cpp'
    return grid.CheckCollision(*this);
}

bool Hitbox::CheckCollision(const ColliderList& list) const
{
    // Implementation is in 'collision/collider_list.cpp'
    return list.CheckCollision(*this);
}

float_t Hitbox::Left() const { return offset.x; }

float_t Hitbox::Right() const { return offset.x + size.x; }

float_t Hitbox::Top() const { return offset.y; }

float_t Hitbox::Bottom() const { return offset.y + size.y; }

float_t Hitbox::AbsoluteLeft() const { return GetActualPosition().x; }

float_t Hitbox::AbsoluteRight() const { return GetActualPosition().x + size.x; }

float_t Hitbox::AbsoluteTop() const { return GetActualPosition().y; }

float_t Hitbox::AbsoluteBottom() const { return GetActualPosition().y + size.y; }

float_t Hitbox::Width() const { return size.x; }

float_t Hitbox::Height() const { return size.y; }

Vector2 Hitbox::Size() const { return size; }
