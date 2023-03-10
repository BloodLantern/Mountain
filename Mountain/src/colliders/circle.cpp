#include "circle.hpp"

#include "draw.hpp"
#include "hitbox.hpp"

#define SQ(x) (x * x)

namespace mountain
{
    Circle::Circle(const Vector2 &position, const float& radius)
        : Collider(position), Radius(radius)
    {
        Type = ColliderType::CIRCLE;
    }

    void Circle::Draw(Color color) const
    {
        Draw::Circle(Position, Radius, color);
    }

    bool Circle::CheckCollision(const Vector2& point) const
    {
        return (point - Position).SquaredNorm() <= SQ(Radius);
    }

    bool Circle::CheckCollision(const Hitbox& hitbox) const
    {
        // Implementation is in 'colliders/hitbox.cpp'
        return hitbox.CheckCollision(*this);
    }

    bool Circle::CheckCollision(const Circle& circle) const
    {
        return (circle.Position - Position).SquaredNorm() < SQ(Radius + circle.Radius);
    }

    bool Circle::Intersect(const Vector2& p1, const Vector2& p2) const
    {
        Vector2 centerProjection = Vector2::DotProduct(p1, (p2 - p1).Normalize()) * p1 + p1;

        if (centerProjection >= p1 && centerProjection <= p2)
            return (centerProjection - Position).SquaredNorm() <= SQ(Radius);
        return false;
    }
}