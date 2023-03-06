#pragma once

#include <vector2.hpp>

#include "color.hpp"

namespace mountain
{
    /// @brief The Draw class is a helper class that
    ///        contains static functions to draw shapes.
    class Draw
    {
    public:
        // You can't instantiate this class.
        Draw() = delete;
        ~Draw() = delete;

        static void DrawLine(const Vector2 p1, const Vector2 p2, const Color color);

        static void DrawRect(const Vector2 position, const Vector2 size, const Color color);
        static void DrawRectFilled(const Vector2 position, const Vector2 size, const Color color);

        static void DrawCircle(const Vector2 position, const float radius, const Color color, const unsigned int segments = 0);
    };
}
