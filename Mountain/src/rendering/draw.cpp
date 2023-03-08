#include "draw.hpp"

#include <numbers>

void mountain::Draw::Points(const Vector2 positions[], const size_t count, const Color color)
{
    glBegin(GL_POINTS);
    glColor4ub(color.r, color.g, color.b, color.a);
    for (size_t i = 0; i < count; i++)
        glVertex2f(positions[i].x, positions[i].y);
    glEnd();
}

void mountain::Draw::Line(const Vector2 &p1, const Vector2 &p2, const Color color)
{
    glBegin(GL_LINES);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void mountain::Draw::Rect(const Vector2& position, const Vector2& size, const Color color)
{
    glBegin(GL_LINE_LOOP);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
}

void mountain::Draw::RectFilled(const Vector2& position, const Vector2& size, const Color color)
{
    glBegin(GL_QUADS);
    glColor4ub(color.r, color.g, color.b, color.a);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
}

void mountain::Draw::Circle(const Vector2& position, const float radius, const Color color, unsigned int segments)
{
    CircleInternal(position, radius, color, segments);
}

void mountain::Draw::CircleFilled(const Vector2 &position, const float radius, const Color color, unsigned int segments)
{
    CircleInternal(position, radius, color, segments, GL_POLYGON);
}

void mountain::Draw::CircleInternal(const Vector2 &position, const float radius, const Color color, unsigned int segments, const GLenum mode)
{
    if (segments == 0)
        segments = 30;

    assert(segments >= 2 && "Cannot draw a circle with less than 2 segments");

    glBegin(mode);
    glColor4ub(color.r, color.g, color.b, color.a);
    const float angle = 2 * (float) std::numbers::pi / segments;
    for (unsigned int i = 0; i < segments; i++)
        glVertex2f(position.x + std::cos(angle * i) * radius, position.y + std::sin(angle * i) * radius);
    glEnd();
}
