#pragma once

#include "collider.hpp"

namespace mountain
{
    class Circle : public Collider
    {
    public:
        float Radius = 0.f;

        Circle() { Type = ColliderType::Circle; }
        Circle(const Vector2& position, const float radius);

        void Draw(const Color color) const override;

        bool CheckCollision(const Vector2& point) const override;
        bool CheckCollision(const Hitbox& hitbox) const override;
        bool CheckCollision(const Circle& circle) const override;
        bool CheckCollision(const Grid& grid) const override;
        bool CheckCollision(const ColliderList& list) const override;

        bool Intersect(const Vector2& p1, const Vector2& p2) const;

        inline float Left() const override { return Position.x; }
        inline float Right() const override { return Position.x + Radius; }
        inline float Top() const override { return Position.y; }
        inline float Bottom() const override { return Position.y + Radius; }
        inline float Width() const override { return Radius * 2; }
        inline float Height() const override { return Radius * 2; }
        inline Vector2 Size() const override { return Vector2(Radius * 2); }
        inline Vector2 Center() const override { return Position; }
    };
}
