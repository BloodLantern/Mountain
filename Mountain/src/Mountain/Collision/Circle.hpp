#pragma once

#include "Mountain/Core.hpp"

#include "Mountain/Collision/Collider.hpp"

namespace Mountain
{
    class MOUNTAIN_API Circle : public Collider
    {
    public:
        f32 radius = 0.f;

        Circle();
        Circle(Vector2 off, f32 radius);

        void RenderDebug(const Color& color) const override;

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
        bool Intersect(Vector2 p1, Vector2 p2) const;

        ATTRIBUTE_NODISCARD
        f32 Left() const override;
        ATTRIBUTE_NODISCARD
        f32 Right() const override;
        ATTRIBUTE_NODISCARD
        f32 Top() const override;
        ATTRIBUTE_NODISCARD
        f32 Bottom() const override;
        ATTRIBUTE_NODISCARD
        Vector2 Center() const override;
        ATTRIBUTE_NODISCARD
        Vector2 TopLeft() const override;
        ATTRIBUTE_NODISCARD
        Vector2 TopRight() const override;
        ATTRIBUTE_NODISCARD
        Vector2 BottomLeft() const override;
        ATTRIBUTE_NODISCARD
        Vector2 BottomRight() const override;

        ATTRIBUTE_NODISCARD
        float AbsoluteLeft() const override;
        ATTRIBUTE_NODISCARD
        float AbsoluteRight() const override;
        ATTRIBUTE_NODISCARD
        float AbsoluteTop() const override;
        ATTRIBUTE_NODISCARD
        float AbsoluteBottom() const override;
        ATTRIBUTE_NODISCARD
        Vector2 AbsoluteCenter() const override;
        ATTRIBUTE_NODISCARD
        Vector2 AbsoluteTopLeft() const override;
        ATTRIBUTE_NODISCARD
        Vector2 AbsoluteTopRight() const override;
        ATTRIBUTE_NODISCARD
        Vector2 AbsoluteBottomLeft() const override;
        ATTRIBUTE_NODISCARD
        Vector2 AbsoluteBottomRight() const override;

        ATTRIBUTE_NODISCARD
        float Width() const override;
        ATTRIBUTE_NODISCARD
        float Height() const override;
        ATTRIBUTE_NODISCARD
        Vector2 Size() const override;
    };
}
