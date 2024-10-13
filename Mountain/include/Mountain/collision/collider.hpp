#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2.hpp>

#include "Mountain/utils/color.hpp"

BEGIN_MOUNTAIN

enum class ColliderType
{
    Hitbox,
    Circle,
    Grid,
    List,

    Count
};

ENUM_COUNT(ColliderType)

class Hitbox;
class Circle;
class Grid;
class ColliderList;

class MOUNTAIN_API Collider
{
    friend class Entity;
    
public:
    Vector2 offset;
    ColliderType type;

    const Vector2* basePosition = nullptr;

    explicit Collider(ColliderType type);
    
    explicit Collider(ColliderType type, Vector2 offset);
    
    virtual ~Collider() = default;

    DEFAULT_COPY_MOVE_OPERATIONS(Collider)

    virtual void DebugRender(const Color& color) const = 0;

    [[nodiscard]]
    virtual Vector2 GetActualPosition() const;

    [[nodiscard]]
    bool_t CheckCollision(const Entity& e) const;
    [[nodiscard]]
    bool_t CheckCollision(const Collider& collider) const;
    [[nodiscard]]
    virtual bool_t CheckCollision(Vector2 point) const = 0;
    [[nodiscard]]
    virtual bool_t CheckCollision(const Hitbox& hitbox) const = 0;
    [[nodiscard]]
    virtual bool_t CheckCollision(const Circle& circle) const = 0;
    [[nodiscard]]
    virtual bool_t CheckCollision(const Grid& grid) const = 0;
    [[nodiscard]]
    virtual bool_t CheckCollision(const ColliderList& list) const = 0;

    [[nodiscard]]
    virtual float_t Left() const = 0;
    [[nodiscard]]
    virtual float_t Right() const = 0;
    [[nodiscard]]
    virtual float_t Top() const = 0;
    [[nodiscard]]
    virtual float_t Bottom() const = 0;
    [[nodiscard]]
    virtual Vector2 Center() const;
    [[nodiscard]]
    virtual Vector2 TopLeft() const;
    [[nodiscard]]
    virtual Vector2 TopRight() const;
    [[nodiscard]]
    virtual Vector2 BottomLeft() const;
    [[nodiscard]]
    virtual Vector2 BottomRight() const;
    
    [[nodiscard]]
    virtual float_t AbsoluteLeft() const = 0;
    [[nodiscard]]
    virtual float_t AbsoluteRight() const = 0;
    [[nodiscard]]
    virtual float_t AbsoluteTop() const = 0;
    [[nodiscard]]
    virtual float_t AbsoluteBottom() const = 0;
    [[nodiscard]]
    virtual Vector2 AbsoluteCenter() const;
    [[nodiscard]]
    virtual Vector2 AbsoluteTopLeft() const;
    [[nodiscard]]
    virtual Vector2 AbsoluteTopRight() const;
    [[nodiscard]]
    virtual Vector2 AbsoluteBottomLeft() const;
    [[nodiscard]]
    virtual Vector2 AbsoluteBottomRight() const;
    
    [[nodiscard]]
    virtual float_t Width() const;
    [[nodiscard]]
    virtual float_t Height() const;
    [[nodiscard]]
    virtual Vector2 Size() const;
};

END_MOUNTAIN
