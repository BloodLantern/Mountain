#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include "Mountain/Utils/Color.hpp"

namespace Mountain
{
    enum class ColliderType : uint8_t
    {
        Hitbox,
        Circle,
        Grid,
        List
    };

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

        virtual void RenderDebug(const Color& color) const = 0;

        ATTRIBUTE_NODISCARD
        virtual Vector2 GetActualPosition() const;

        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(const Entity& e) const;
        ATTRIBUTE_NODISCARD
        bool_t CheckCollision(const Collider& collider) const;
        ATTRIBUTE_NODISCARD
        virtual bool_t CheckCollision(Vector2 point) const = 0;
        ATTRIBUTE_NODISCARD
        virtual bool_t CheckCollision(const Hitbox& hitbox) const = 0;
        ATTRIBUTE_NODISCARD
        virtual bool_t CheckCollision(const Circle& circle) const = 0;
        ATTRIBUTE_NODISCARD
        virtual bool_t CheckCollision(const Grid& grid) const = 0;
        ATTRIBUTE_NODISCARD
        virtual bool_t CheckCollision(const ColliderList& list) const = 0;

        ATTRIBUTE_NODISCARD
        virtual float_t Left() const = 0;
        ATTRIBUTE_NODISCARD
        virtual float_t Right() const = 0;
        ATTRIBUTE_NODISCARD
        virtual float_t Top() const = 0;
        ATTRIBUTE_NODISCARD
        virtual float_t Bottom() const = 0;
        ATTRIBUTE_NODISCARD
        virtual Vector2 Center() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 TopLeft() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 TopRight() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 BottomLeft() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 BottomRight() const;

        ATTRIBUTE_NODISCARD
        virtual float_t AbsoluteLeft() const = 0;
        ATTRIBUTE_NODISCARD
        virtual float_t AbsoluteRight() const = 0;
        ATTRIBUTE_NODISCARD
        virtual float_t AbsoluteTop() const = 0;
        ATTRIBUTE_NODISCARD
        virtual float_t AbsoluteBottom() const = 0;
        ATTRIBUTE_NODISCARD
        virtual Vector2 AbsoluteCenter() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 AbsoluteTopLeft() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 AbsoluteTopRight() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 AbsoluteBottomLeft() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 AbsoluteBottomRight() const;

        ATTRIBUTE_NODISCARD
        virtual float_t Width() const;
        ATTRIBUTE_NODISCARD
        virtual float_t Height() const;
        ATTRIBUTE_NODISCARD
        virtual Vector2 Size() const;
    };
}
