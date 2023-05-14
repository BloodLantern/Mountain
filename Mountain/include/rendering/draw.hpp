#pragma once

#include <vector2.hpp>
#include <GLFW/glfw3.h>

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

        static void Points(const Vector2 positions[], const size_t count, const Color color = Color::White);

        static void Line(const Vector2& p1, const Vector2& p2, const Color color = Color::White);

        static void Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color color = Color::White);
        static void TriangleFilled(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color color = Color::White);

        static void Rect(const Vector2& position, const Vector2& size, const Color color = Color::White);
        static void RectFilled(const Vector2& position, const Vector2& size, const Color color = Color::White);

        static void Circle(const Vector2& position, const float radius, const Color color = Color::White, unsigned int segments = 0);
        static void CircleFilled(const Vector2& position, const float radius, const Color color = Color::White, unsigned int segments = 0);

        static void Image(const unsigned int textureId, const Vector2& position, const Vector2& size, const Vector2& uv0 = 0, const Vector2& uv1 = 1, const Color color = Color::White);

    private:
        static void CircleInternal(const Vector2& position, const float radius, const Color color = Color::White, unsigned int segments = 0, const GLenum mode = GL_LINE_LOOP);
    };
}
