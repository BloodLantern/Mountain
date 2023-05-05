#include "hitbox.hpp"

#include "draw.hpp"
#include "circle.hpp"
#include "grid.hpp"

mountain::Hitbox::Hitbox(const Vector2 &position, const Vector2& size)
    : Collider(position), BoxSize(size)
{
    Type = ColliderType::HITBOX;
}

void mountain::Hitbox::Draw(const Color color) const
{
    Draw::Rect(Position, BoxSize, color);
}

bool mountain::Hitbox::Intersects(const Hitbox &other) const
{
    Vector2 position = other.Position, size = other.BoxSize;

    // Check for a collision with any of the hitbox's corners
    return CheckCollision(position) // Top left
        || CheckCollision(Vector2(position.x + size.x, position.y)) // Top right
        || CheckCollision(Vector2(position.x, position.y + size.y)) // Bottom left
        || CheckCollision(Vector2(position.x + size.x, position.y + size.y)); // Bottom right
}

bool mountain::Hitbox::CheckCollision(const Vector2& point) const
{
    return point.x < Right() && point.x > Left()
        && point.y < Bottom() && point.y > Top();
}

bool mountain::Hitbox::CheckCollision(const Hitbox& hitbox) const
{
    if (Intersects(hitbox))
        return true;

    // Check if one of the edges is inside this hitbox
    return hitbox.Left() < Right() && hitbox.Right() > Left()
        && hitbox.Top() < Bottom() && hitbox.Bottom() > Top();
}

bool mountain::Hitbox::CheckCollision(const Circle& circle) const
{
    if (CheckCollision(circle.Position))
        return true;

    const Vector2& topLeft = Position;
    const Vector2 topRight(Position.x + BoxSize.x, Position.y),
        bottomLeft(Position.x, Position.y + BoxSize.y),
        bottomRight(Position.x + BoxSize.x, Position.y + BoxSize.y);
            
    return circle.Intersect(topLeft, topRight)
        || circle.Intersect(topRight, bottomRight)
        || circle.Intersect(bottomRight, bottomLeft)
        || circle.Intersect(bottomLeft, topLeft);
}

bool mountain::Hitbox::CheckCollision(const Grid &grid) const
{
    // Implementation is in 'colliders/grid.cpp'
    return grid.CheckCollision(*this);
}
