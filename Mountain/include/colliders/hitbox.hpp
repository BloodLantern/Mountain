#pragma once

#include "collider.hpp"

namespace mountain
{
    class Hitbox : public Collider
    {
    public:
        Hitbox() { mType = ColliderType::HITBOX; }
        Hitbox(const Vector2& position, const Vector2& size);

        void Draw(Color color) const override;

        bool CheckCollision(const Vector2& point) const override;
        bool CheckCollision(const Hitbox& hitbox) const override;
        bool CheckCollision(const Circle& circle) const override;

        inline float Left() const override { return mPosition.x; }
        inline float Right() const override { return mPosition.x + mSize.x; }
        inline float Top() const override { return mPosition.y; }
        inline float Bottom() const override { return mPosition.y + mSize.y; }
        inline Vector2 Center() const override { return mPosition + mSize / 2; }

        Vector2 GetSize() const { return mSize; }
        void SetSize(const Vector2& size) { mSize = size; }

    private:
        Vector2 mSize;
    };
}
