#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Collision/Circle.hpp"

#include "Mountain/Collision/ColliderList.hpp"
#include "Mountain/Collision/Grid.hpp"
#include "Mountain/Collision/Hitbox.hpp"
#include "Mountain/Rendering/Draw.hpp"

using namespace Mountain;

Circle::Circle()
    : Collider(ColliderType::Circle)
{
}

Circle::Circle(const Vector2 off, const float_t radius)
    : Collider(ColliderType::Circle, off)
    , radius(radius)
{
}

void Circle::RenderDebug(const Color& color) const
{
    Draw::Circle(GetActualPosition(), radius, 1.f, Vector2::One(), color);
}

bool Circle::CheckCollision(const Vector2 point) const
{
    return (point - GetActualPosition()).SquaredLength() <= SQ(radius);
}

bool Circle::CheckCollision(const Hitbox& hitbox) const
{
    // Implementation is in 'collision/hitbox.cpp'
    return hitbox.CheckCollision(*this);
}

bool Circle::CheckCollision(const Circle& circle) const
{
    return (circle.GetActualPosition() - GetActualPosition()).SquaredLength() < SQ(radius + circle.radius);
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

bool Circle::Intersect(const Vector2 p1, const Vector2 p2) const
{
    const Vector2 position = GetActualPosition();
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

float_t Circle::Left() const { return offset.x - radius; }

float_t Circle::Right() const { return offset.x + radius; }

float_t Circle::Top() const { return offset.y - radius; }

float_t Circle::Bottom() const { return offset.y + radius; }

Vector2 Circle::Center() const { return offset; }

Vector2 Circle::TopLeft() const { return Center() + Vector2{ std::cos(3.f * Calc::PiOver4) * radius, std::sin(3.f * Calc::PiOver4) * radius }; }

Vector2 Circle::TopRight() const { return Center() + Vector2{ std::cos(Calc::PiOver4) * radius, std::sin(Calc::PiOver4) * radius }; }

Vector2 Circle::BottomLeft() const { return Center() + Vector2{ std::cos(-3.f * Calc::PiOver4) * radius, std::sin(-3.f * Calc::PiOver4) * radius }; }

Vector2 Circle::BottomRight() const { return Center() + Vector2{ std::cos(-Calc::PiOver4) * radius, std::sin(-Calc::PiOver4) * radius }; }

float Circle::AbsoluteLeft() const { return GetActualPosition().x - radius; }

float Circle::AbsoluteRight() const { return GetActualPosition().x + radius; }

float Circle::AbsoluteTop() const { return GetActualPosition().y - radius; }

float Circle::AbsoluteBottom() const { return GetActualPosition().y + radius; }

Vector2 Circle::AbsoluteCenter() const { return GetActualPosition(); }

Vector2 Circle::AbsoluteTopLeft() const { return AbsoluteCenter() + Vector2{ std::cos(3.f * Calc::PiOver4) * radius, std::sin(3.f * Calc::PiOver4) * radius }; }

Vector2 Circle::AbsoluteTopRight() const { return AbsoluteCenter() + Vector2{ std::cos(Calc::PiOver4) * radius, std::sin(Calc::PiOver4) * radius }; }

Vector2 Circle::AbsoluteBottomLeft() const { return AbsoluteCenter() + Vector2{ std::cos(-3.f * Calc::PiOver4) * radius, std::sin(-3.f * Calc::PiOver4) * radius }; }

Vector2 Circle::AbsoluteBottomRight() const { return AbsoluteCenter() + Vector2{ std::cos(-Calc::PiOver4) * radius, std::sin(-Calc::PiOver4) * radius }; }

float Circle::Width() const { return radius * 2.f; }

float Circle::Height() const { return radius * 2.f; }

Vector2 Circle::Size() const { return Vector2{ radius * 2.f }; }
