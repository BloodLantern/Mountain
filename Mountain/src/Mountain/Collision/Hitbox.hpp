#pragma once

#include "Mountain/Collision/Collider.hpp"
#include "Mountain/Utils/Rectangle.hpp"

namespace Mountain
{
    class MOUNTAIN_API Hitbox : public Collider
    {
    public:
        Vector2 size;

        Hitbox();

        Hitbox(Vector2 off, Vector2 size);

        void RenderDebug(const Color& color) const override;

        ATTRIBUTE_NODISCARD
        constexpr Rectangle ToRectangle() const;

        ATTRIBUTE_NODISCARD
        bool Intersects(const Hitbox& other) const;

        using Collider::CheckCollision;
        ATTRIBUTE_NODISCARD
        bool CheckCollision(Vector2 point) const override;
        ATTRIBUTE_NODISCARD
        bool CheckCollision(const Hitbox& hitbox) const override;
        ATTRIBUTE_NODISCARD
        bool CheckCollision(const Circle& circle) const override;
        ATTRIBUTE_NODISCARD
        bool CheckCollision(const Grid& grid) const override;
        ATTRIBUTE_NODISCARD
        bool CheckCollision(const ColliderList& list) const override;

        ATTRIBUTE_NODISCARD
        f32 Left() const override;
        ATTRIBUTE_NODISCARD
        f32 Right() const override;
        ATTRIBUTE_NODISCARD
        f32 Top() const override;
        ATTRIBUTE_NODISCARD
        f32 Bottom() const override;

        ATTRIBUTE_NODISCARD
        f32 AbsoluteLeft() const override;
        ATTRIBUTE_NODISCARD
        f32 AbsoluteRight() const override;
        ATTRIBUTE_NODISCARD
        f32 AbsoluteTop() const override;
        ATTRIBUTE_NODISCARD
        f32 AbsoluteBottom() const override;

        ATTRIBUTE_NODISCARD
        f32 Width() const override;
        ATTRIBUTE_NODISCARD
        f32 Height() const override;
        ATTRIBUTE_NODISCARD
        Vector2 Size() const override;
    };
}

// Start of Hitbox.inl

namespace Mountain
{
    constexpr Rectangle Hitbox::ToRectangle() const { return { GetActualPosition(), size }; }
}
