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

// TODO - Add a Vector2* that points to the attached Entity's position and rename the current 'position' Vector2 to 'offset'

class MOUNTAIN_API Collider
{
    friend class Entity;
    
public:
    Vector2 position;
    ColliderType type;

    explicit Collider(ColliderType type);
    
    explicit Collider(ColliderType type, const Vector2& position);
    
    virtual ~Collider() = default;

    DEFAULT_COPY_MOVE_OPERATIONS(Collider)

    virtual void DebugRender(const Color& color) const = 0;

    [[nodiscard]]
    bool_t CheckCollision(const Entity& e) const;
    [[nodiscard]]
    bool_t CheckCollision(const Collider& collider) const;
    [[nodiscard]]
    virtual bool_t CheckCollision(const Vector2& point) const = 0;
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
    virtual float_t Width() const;
    [[nodiscard]]
    virtual float_t Height() const;
    [[nodiscard]]
    virtual Vector2 Size() const;
    [[nodiscard]]
    virtual Vector2 Center() const;

    /// @brief Get the Entity on which this Component is attached
    [[nodiscard]]
    const Entity* GetEntity() const;
    
    /// @brief Get the Entity on which this Component is attached
    Entity* GetEntity();

private:
    Entity* m_Entity = nullptr;
};

END_MOUNTAIN
