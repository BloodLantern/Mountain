#include "circle.hpp"

#include "draw.hpp"
#include "hitbox.hpp"

#define SQ(x) (x * x)

mountain::Circle::Circle(const Vector2& position, const float radius)
    : Collider(position), Radius(radius)
{
    Type = ColliderType::CIRCLE;
}

void mountain::Circle::Draw(const Color color) const
{
    Draw::Circle(Position, Radius, color);
}

bool mountain::Circle::CheckCollision(const Vector2& point) const
{
    return (point - Position).SquaredNorm() <= SQ(Radius);
}

bool mountain::Circle::CheckCollision(const Hitbox& hitbox) const
{
    // Implementation is in 'colliders/hitbox.cpp'
    return hitbox.CheckCollision(*this);
}

bool mountain::Circle::CheckCollision(const Circle& circle) const
{
    return (circle.Position - Position).SquaredNorm() < SQ(Radius + circle.Radius);
}

bool mountain::Circle::Intersect(const Vector2& p1, const Vector2& p2) const
{
    // Code from: https://stackoverflow.com/questions/67116296/is-this-code-for-determining-if-a-circle-and-line-segment-intersects-correct

    const float x_linear = p2.x - p1.x;
    const float x_constant = p1.x - Position.x;
    const float y_linear = p2.y - p1.y;
    const float y_constant = p1.y - Position.y;
    const float a = x_linear * x_linear + y_linear * y_linear;
    const float half_b = x_linear * x_constant + y_linear * y_constant;
    const float c = x_constant * x_constant + y_constant * y_constant - SQ(Radius);
    
    return (
        half_b * half_b >= a * c &&
        (-half_b <= a || c + half_b + half_b + a <= 0) &&
        (half_b <= 0 || c <= 0)
    );
}
