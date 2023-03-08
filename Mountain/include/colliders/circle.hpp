#pragma once

#include "collider.hpp"

namespace mountain
{
    class Circle : public Collider
    {
    public:
        Circle() { mType = ColliderType::CIRCLE; }
        Circle(const Vector2& position, const float& radius);

        void Draw(Color color) const override;

        bool CheckCollision(const Vector2& point) const override;
        bool CheckCollision(const Hitbox& hitbox) const override;
        bool CheckCollision(const Circle& circle) const override;

        bool Intersect(const Vector2& p1, const Vector2& p2) const;

        inline float Left() const override { return mPosition.x; }
        inline float Right() const override { return mPosition.x + mRadius; }
        inline float Top() const override { return mPosition.y; }
        inline float Bottom() const override { return mPosition.y + mRadius; }
        inline Vector2 Center() const override { return mPosition; }

    private:
        float mRadius = 0.f;
    };
}
