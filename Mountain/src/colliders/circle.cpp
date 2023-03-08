#include "circle.hpp"

#include "draw.hpp"
#include "hitbox.hpp"

namespace mountain
{
    Circle::Circle(const Vector2 &position, const float& radius)
        : Collider(position), mRadius(radius)
    {
        mType = ColliderType::CIRCLE;
    }

    void Circle::Draw(Color color) const
    {
        Draw::Circle(mPosition, mRadius, color);
    }

    bool Circle::CheckCollision(const Vector2& point) const
    {
        return (point - mPosition).Norm() <= mRadius;
    }

    bool Circle::CheckCollision(const Hitbox& hitbox) const
    {
        // Implementation is in 'colliders/hitbox.cpp'
        return hitbox.CheckCollision(*this);
    }

    bool Circle::CheckCollision(const Circle& circle) const
    {
        return (circle.mPosition - mPosition).Norm() < mRadius + circle.mRadius;
    }

    bool Circle::Intersect(const Vector2& p1, const Vector2& p2) const
    {
        Vector2 centerProjection = Vector2::DotProduct(p1, (p2 - p1).Normalize()) * p1 + p1;

        if (centerProjection >= p1 && centerProjection <= p2)
            return std::abs((centerProjection - mPosition).Norm()) <= mRadius;
        return false;
    }
}