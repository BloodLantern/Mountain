#pragma once

#include "Mountain/Core.hpp"

#include <Maths/vector2.hpp>

namespace Mountain
{
    class MOUNTAIN_API Rectangle
    {
    public:
        Vector2 position, size;

        Rectangle() = default;
        explicit constexpr Rectangle(Vector2 size);
        constexpr Rectangle(Vector2 position, Vector2 size);

        [[nodiscard]]
        constexpr float Left() const;
        [[nodiscard]]
        constexpr float Right() const;
        [[nodiscard]]
        constexpr float Top() const;
        [[nodiscard]]
        constexpr float Bottom() const;

        [[nodiscard]]
        constexpr Vector2 Center() const;
        [[nodiscard]]
        constexpr Vector2 TopLeft() const;
        [[nodiscard]]
        constexpr Vector2 TopRight() const;
        [[nodiscard]]
        constexpr Vector2 BottomLeft() const;
        [[nodiscard]]
        constexpr Vector2 BottomRight() const;

        [[nodiscard]]
        constexpr float Width() const;
        [[nodiscard]]
        constexpr float Height() const;
    };
}

// Start of Rectangle.inl

namespace Mountain
{
    constexpr Rectangle::Rectangle(const Vector2 size): size(size) {}

    constexpr Rectangle::Rectangle(const Vector2 position, const Vector2 size) : position(position), size(size) {}

    constexpr float Rectangle::Left() const { return position.x; }

    constexpr float Rectangle::Right() const { return position.x + size.x; }

    constexpr float Rectangle::Top() const { return position.y; }

    constexpr float Rectangle::Bottom() const { return position.y + size.y; }

    constexpr Vector2 Rectangle::Center() const { return position + size / 2; }

    constexpr Vector2 Rectangle::TopLeft() const { return position; }

    constexpr Vector2 Rectangle::TopRight() const { return position + Vector2(size.x, 0.f); }

    constexpr Vector2 Rectangle::BottomLeft() const { return position + Vector2(0.f, size.y); }

    constexpr Vector2 Rectangle::BottomRight() const { return position + size; }

    constexpr float Rectangle::Width() const { return size.x; }

    constexpr float Rectangle::Height() const { return size.y; }
}
