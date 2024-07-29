#include "collision/hitbox.hpp"

#include "draw.hpp"
#include "collision/circle.hpp"
#include "collision/collider_list.hpp"
#include "collision/grid.hpp"

using namespace Mountain;
Hitbox::Hitbox(const Vector2& position, const Vector2& size)  // NOLINT(clang-diagnostic-shadow-field)
    : Collider(ColliderType::Hitbox, position)
    , size(size)
{
}

void Hitbox::DebugRender(const Color& color) const
{
    Draw::Rectangle(position, size, color);
}

bool Hitbox::Intersects(const Hitbox &other) const
{
    const Vector2 otherPosition = other.position;
    const Vector2 otherSize = other.size;

    // Check for a collision with any of the hitbox's corners
    return CheckCollision(otherPosition) // Top left
        || CheckCollision(Vector2(otherPosition.x + otherSize.x, otherPosition.y)) // Top right
        || CheckCollision(Vector2(otherPosition.x, otherPosition.y + otherSize.y)) // Bottom left
        || CheckCollision(Vector2(otherPosition.x + otherSize.x, otherPosition.y + otherSize.y)); // Bottom right
}

bool Hitbox::CheckCollision(const Vector2& point) const
{
    return point.x < Right() && point.x > Left()
        && point.y < Bottom() && point.y > Top();
}

bool Hitbox::CheckCollision(const Hitbox& hitbox) const
{
    if (Intersects(hitbox))
        return true;

    // Check if one of the edges is inside this hitbox
    return hitbox.Left() < Right() && hitbox.Right() > Left()
        && hitbox.Top() < Bottom() && hitbox.Bottom() > Top();
}

bool Hitbox::CheckCollision(const Circle& circle) const
{
    if (CheckCollision(circle.position))
        return true;

    const Vector2& topLeft = position;
    const Vector2 topRight(position.x + size.x, position.y),
        bottomLeft(position.x, position.y + size.y),
        bottomRight(position.x + size.x, position.y + size.y);
            
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

float Hitbox::Left() const { return ToRectangle().Left(); }

float Hitbox::Right() const { return ToRectangle().Right(); }

float Hitbox::Top() const { return ToRectangle().Top(); }

float Hitbox::Bottom() const { return ToRectangle().Bottom(); }

Vector2 Hitbox::Center() const { return ToRectangle().Center(); }

float Hitbox::Width() const { return ToRectangle().Width(); }

float Hitbox::Height() const { return ToRectangle().Height(); }

Vector2 Hitbox::Size() const { return size; }
