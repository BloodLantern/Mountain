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
        bool_t Intersects(const Hitbox& other) const;

        using Collider::CheckCollision;
        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(Vector2 point) const override;
        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(const Hitbox& hitbox) const override;
        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(const Circle& circle) const override;
        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(const Grid& grid) const override;
        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(const ColliderList& list) const override;

        ATTRIBUTE_NODISCARD
        float_t Left() const override;
        ATTRIBUTE_NODISCARD
        float_t Right() const override;
        ATTRIBUTE_NODISCARD
        float_t Top() const override;
        ATTRIBUTE_NODISCARD
        float_t Bottom() const override;

        ATTRIBUTE_NODISCARD
        float_t AbsoluteLeft() const override;
        ATTRIBUTE_NODISCARD
        float_t AbsoluteRight() const override;
        ATTRIBUTE_NODISCARD
        float_t AbsoluteTop() const override;
        ATTRIBUTE_NODISCARD
        float_t AbsoluteBottom() const override;

        ATTRIBUTE_NODISCARD
        float_t Width() const override;
        ATTRIBUTE_NODISCARD
        float_t Height() const override;
        ATTRIBUTE_NODISCARD
        Vector2 Size() const override;
    };
}

// Start of Hitbox.inl

namespace Mountain
{
    constexpr Rectangle Hitbox::ToRectangle() const { return { GetActualPosition(), size }; }
}
