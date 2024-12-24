#pragma once

#include "Mountain/core.hpp"

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

#include "Mountain/utils/rectangle.inl"
