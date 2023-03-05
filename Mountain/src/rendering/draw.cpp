#include "draw.hpp"

#include <GLFW/glfw3.h>
#include <numbers>

void mountain::Draw::DrawLine(const Vector2 p1, const Vector2 p2, const Color color)
{
    glBegin(GL_LINES);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void mountain::Draw::DrawRect(const Vector2 position, const Vector2 size, const Color color)
{
    glBegin(GL_LINE_LOOP);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
}

void mountain::Draw::DrawRectFilled(const Vector2 position, const Vector2 size, const Color color)
{
    glBegin(GL_QUADS);
    printf("%f %f %f %f\n", position.x, position.y, size.x, size.y);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
}

void mountain::Draw::DrawCircle(const Vector2 position, const float radius, const Color color, const unsigned int segments)
{
    assert(segments >= 2 && "Cannot draw a circle with less than 2 segments");

    glBegin(GL_LINE_LOOP);
    glColor4ub(color.r, color.g, color.b, color.a);
    const float angle = 2 * (float) std::numbers::pi / segments;
    for (unsigned int i = 0; i < segments; i++)
        glVertex2f(position.x + std::cos(angle * i) * radius, position.y + std::sin(angle * i) * radius);
    glEnd();
}
