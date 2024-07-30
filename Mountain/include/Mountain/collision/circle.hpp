#pragma once

#include "Mountain/core.hpp"

#include "Mountain/collision/collider.hpp"

BEGIN_MOUNTAIN

class MOUNTAIN_API Circle : public Collider
{
public:
    float_t radius = 0.f;

    Circle();
    Circle(const Vector2& position, float_t radius);

    void DebugRender(const Color& color) const override;

    [[nodiscard]]
    bool CheckCollision(const Vector2& point) const override;
    [[nodiscard]]
    bool CheckCollision(const Hitbox& hitbox) const override;
    [[nodiscard]]
    bool CheckCollision(const Circle& circle) const override;
    [[nodiscard]]
    bool CheckCollision(const Grid& grid) const override;
    [[nodiscard]]
    bool CheckCollision(const ColliderList& list) const override;

    [[nodiscard]]
    bool Intersect(const Vector2& p1, const Vector2& p2) const;

    [[nodiscard]]
    float Left() const override;
    [[nodiscard]]
    float Right() const override;
    [[nodiscard]]
    float Top() const override;
    [[nodiscard]]
    float Bottom() const override;
    [[nodiscard]]
    Vector2 Center() const override;
    [[nodiscard]]
    float Width() const override;
    [[nodiscard]]
    float Height() const override;
    [[nodiscard]]
    Vector2 Size() const override;
};

END_MOUNTAIN
