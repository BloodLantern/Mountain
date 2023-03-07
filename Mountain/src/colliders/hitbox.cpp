#include "colliders/hitbox.hpp"

#include "draw.hpp"
#include "colliders/circle.hpp"

namespace mountain
{
    Hitbox::Hitbox(const Vector2 &position, const Vector2& size)
        : Collider(position), mSize(size)
    {
        mType = ColliderType::HITBOX;
    }

    void Hitbox::Draw(Color color) const
    {
        Draw::Rect(mPosition, mPosition + mSize, color);
    }

    bool Hitbox::CheckCollision(const Vector2& point) const
    {
        return point.x < Right() && point.x > Left()
            && point.y < Bottom() && point.y > Top();
    }

    bool Hitbox::CheckCollision(const Hitbox& hitbox) const
    {
        Vector2 position = hitbox.mPosition, size = hitbox.mSize;

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
        if (CheckCollision(circle.GetPosition()))
            return true;

        const Vector2& topLeft = mPosition;
        const Vector2 topRight(mPosition.x + mSize.x, mPosition.y),
            bottomLeft(mPosition.x, mPosition.y + mSize.y),
            bottomRight(mPosition.x + mSize.x, mPosition.y + mSize.y);
            
        return circle.Intersect(topLeft, topRight)
            || circle.Intersect(topRight, bottomRight)
            || circle.Intersect(bottomRight, bottomLeft)
            || circle.Intersect(bottomLeft, topLeft);
    }
}