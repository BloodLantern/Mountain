#pragma once

#include "core.hpp"

#include <Maths/vector2.hpp>

BEGIN_MOUNTAIN

class MOUNTAIN_API Rectangle
{
public:
    Vector2 position, size;

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
    constexpr float Width() const;
    [[nodiscard]]
    constexpr float Height() const;
};

END_MOUNTAIN

#include "utils/rectangle.inl"
