#pragma once

#include "collider.hpp"

namespace mountain
{
    class Hitbox : public Collider
    {
    public:
        Vector2 Size;

        Hitbox() { Type = ColliderType::HITBOX; }
        Hitbox(const Vector2& position, const Vector2& size);

        void Draw(Color color) const override;

        bool CheckCollision(const Vector2& point) const override;
        bool CheckCollision(const Hitbox& hitbox) const override;
        bool CheckCollision(const Circle& circle) const override;

        inline float Left() const override { return Position.x; }
        inline float Right() const override { return Position.x + Size.x; }
        inline float Top() const override { return Position.y; }
        inline float Bottom() const override { return Position.y + Size.y; }
        inline Vector2 Center() const override { return Position + Size / 2; }
        virtual inline float Width() const { return Size.x; }
        virtual inline float Height() const { return Size.y; }
        virtual inline Vector2 Size() const { return Size; }

        Vector2 GetSize() const { return Size; }
        void SetSize(const Vector2& size) { Size = size; }
    };
}
