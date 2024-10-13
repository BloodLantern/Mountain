#pragma once

#include "Mountain/core.hpp"

#include "Mountain/collision/collider.hpp"

BEGIN_MOUNTAIN

class MOUNTAIN_API Circle : public Collider
{
public:
    float_t radius = 0.f;

    Circle();
    Circle(Vector2 position, float_t radius);

    void DebugRender(const Color& color) const override;

    [[nodiscard]]
    bool CheckCollision(Vector2 point) const override;
    [[nodiscard]]
    bool CheckCollision(const Hitbox& hitbox) const override;
    [[nodiscard]]
    bool CheckCollision(const Circle& circle) const override;
    [[nodiscard]]
    bool CheckCollision(const Grid& grid) const override;
    [[nodiscard]]
    bool CheckCollision(const ColliderList& list) const override;

    [[nodiscard]]
    bool Intersect(Vector2 p1, Vector2 p2) const;

    [[nodiscard]]
    float_t Left() const override;
    [[nodiscard]]
    float_t Right() const override;
    [[nodiscard]]
    float_t Top() const override;
    [[nodiscard]]
    float_t Bottom() const override;
    [[nodiscard]]
    Vector2 Center() const override;
    [[nodiscard]]
    Vector2 TopLeft() const override;
    [[nodiscard]]
    Vector2 TopRight() const override;
    [[nodiscard]]
    Vector2 BottomLeft() const override;
    [[nodiscard]]
    Vector2 BottomRight() const override;
    
    [[nodiscard]]
    float AbsoluteLeft() const override;
    [[nodiscard]]
    float AbsoluteRight() const override;
    [[nodiscard]]
    float AbsoluteTop() const override;
    [[nodiscard]]
    float AbsoluteBottom() const override;
    [[nodiscard]]
    Vector2 AbsoluteCenter() const override;
    [[nodiscard]]
    Vector2 AbsoluteTopLeft() const override;
    [[nodiscard]]
    Vector2 AbsoluteTopRight() const override;
    [[nodiscard]]
    Vector2 AbsoluteBottomLeft() const override;
    [[nodiscard]]
    Vector2 AbsoluteBottomRight() const override;
    
    [[nodiscard]]
    float Width() const override;
    [[nodiscard]]
    float Height() const override;
    [[nodiscard]]
    Vector2 Size() const override;
};

END_MOUNTAIN
