#pragma once

#include "collider.hpp"

namespace mountain
{
    class Hitbox : public Collider
    {
    public:
        Vector2 BoxSize;

        Hitbox() { Type = ColliderType::HITBOX; }
        Hitbox(const Vector2& position, const Vector2& size);

        void Draw(const Color& color) const override;

        bool CheckCollision(const Vector2& point) const override;
        bool CheckCollision(const Hitbox& hitbox) const override;
        bool CheckCollision(const Circle& circle) const override;

        inline float Left() const override { return Position.x; }
        inline float Right() const override { return Position.x + BoxSize.x; }
        inline float Top() const override { return Position.y; }
        inline float Bottom() const override { return Position.y + BoxSize.y; }
        inline Vector2 Center() const override { return Position + BoxSize / 2; }
        virtual inline float Width() const { return BoxSize.x; }
        virtual inline float Height() const { return BoxSize.y; }
        virtual inline Vector2 Size() const { return BoxSize; }
    };
}
