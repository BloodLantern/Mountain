#pragma once

#include <vector2.hpp>

#include "color.hpp"

namespace mountain
{
    class Draw
    {
    public:
        static void DrawLine(const Vector2 p1, const Vector2 p2, const Color color);

        static void DrawRect(const Vector2 position, const Vector2 size, const Color color);
        static void DrawRectFilled(const Vector2 position, const Vector2 size, const Color color);

        static void DrawCircle(const Vector2 position, const float radius, const Color color, const unsigned int segments = 0);
    };
}
