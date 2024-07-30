#pragma once

#include "Mountain/collision/collider.hpp"
#include "Mountain/utils/rectangle.hpp"

BEGIN_MOUNTAIN

class MOUNTAIN_API Hitbox : public Collider
{
public:
    Vector2 size;

    Hitbox();

    Hitbox(const Vector2& position, const Vector2& size);

    void DebugRender(const Color& color) const override;

    [[nodiscard]]
    constexpr Rectangle ToRectangle() const;

    [[nodiscard]]
    bool Intersects(const Hitbox& other) const;

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

#include "Mountain/collision/hitbox.inl"
