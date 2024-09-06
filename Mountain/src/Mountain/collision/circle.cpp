#include "Mountain/collision/circle.hpp"

#include "Mountain/collision/collider_list.hpp"
#include "Mountain/collision/grid.hpp"
#include "Mountain/collision/hitbox.hpp"
#include "Mountain/rendering/draw.hpp"

using namespace Mountain;

Circle::Circle()
    : Collider(ColliderType::Circle)
{
}

Circle::Circle(const Vector2& position, const float_t radius)  // NOLINT(clang-diagnostic-shadow-field)
    : Collider(ColliderType::Circle, position)
    , radius(radius)
{
}

void Circle::DebugRender(const Color& color) const
{
    Draw::Circle(position, radius, false, color);
}

bool Circle::CheckCollision(const Vector2& point) const
{
    return (point - position).SquaredLength() <= SQ(radius);
}

bool Circle::CheckCollision(const Hitbox& hitbox) const
{
    // Implementation is in 'collision/hitbox.cpp'
    return hitbox.CheckCollision(*this);
}

bool Circle::CheckCollision(const Circle& circle) const
{
    return (circle.position - position).SquaredLength() < SQ(radius + circle.radius);
}

bool Circle::CheckCollision(const Grid &grid) const
{
    // Implementation is in 'collision/grid.cpp'
    return grid.CheckCollision(*this);
}

bool Circle::CheckCollision(const ColliderList& list) const
{
    // Implementation is in 'collision/collider_list.cpp'
    return list.CheckCollision(*this);
}

bool Circle::Intersect(const Vector2& p1, const Vector2& p2) const
{
    // Code from: https://stackoverflow.com/questions/67116296/is-this-code-for-determining-if-a-circle-and-line-segment-intersects-correct

    const float xLinear = p2.x - p1.x;
    const float xConstant = p1.x - position.x;
    const float yLinear = p2.y - p1.y;
    const float yConstant = p1.y - position.y;
    const float a = xLinear * xLinear + yLinear * yLinear;
    const float halfB = xLinear * xConstant + yLinear * yConstant;
    const float c = xConstant * xConstant + yConstant * yConstant - SQ(radius);
    
    return (
        halfB * halfB >= a * c &&
        (-halfB <= a || c + halfB + halfB + a <= 0.f) &&
        (halfB <= 0.f || c <= 0.f)
    );
}

float Circle::Left() const { return position.x; }

float Circle::Right() const { return position.x + radius; }

float Circle::Top() const { return position.y; }

float Circle::Bottom() const { return position.y + radius; }

Vector2 Circle::Center() const { return position; }

float Circle::Width() const { return radius * 2; }

float Circle::Height() const { return radius * 2; }

Vector2 Circle::Size() const { return Vector2(radius * 2); }
