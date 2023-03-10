#include "hitbox.hpp"

#include "draw.hpp"
#include "circle.hpp"

namespace mountain
{
    Hitbox::Hitbox(const Vector2 &position, const Vector2& size)
        : Collider(position), Size(size)
    {
        Type = ColliderType::HITBOX;
    }

    void Hitbox::Draw(Color color) const
    {
        Draw::Rect(Position, Position + Size, color);
    }

    bool Hitbox::CheckCollision(const Vector2& point) const
    {
        return point.x < Right() && point.x > Left()
            && point.y < Bottom() && point.y > Top();
    }

    bool Hitbox::CheckCollision(const Hitbox& hitbox) const
    {
        Vector2 position = hitbox.Position, size = hitbox.Size;

        // Check for a collision with any of the hitbox's corners
        if (CheckCollision(position) // Top left
            || CheckCollision(Vector2(position.x + size.x, position.y)) // Top right
            || CheckCollision(Vector2(position.x, position.y + size.y)) // Bottom left
            || CheckCollision(Vector2(position.x + size.x, position.y + size.y))) // Bottom right
            return true;

        // Check if one of the edges is inside this hitbox
        return hitbox.Left() < Right() && hitbox.Right() > Left()
            && hitbox.Top() < Bottom() && hitbox.Bottom() > Top();
    }

    bool Hitbox::CheckCollision(const Circle& circle) const
    {
        if (CheckCollision(circle.Position))
            return true;

        const Vector2& topLeft = Position;
        const Vector2 topRight(Position.x + Size.x, Position.y),
            bottomLeft(Position.x, Position.y + Size.y),
            bottomRight(Position.x + Size.x, Position.y + Size.y);
            
        return circle.Intersect(topLeft, topRight)
            || circle.Intersect(topRight, bottomRight)
            || circle.Intersect(bottomRight, bottomLeft)
            || circle.Intersect(bottomLeft, topLeft);
    }
}