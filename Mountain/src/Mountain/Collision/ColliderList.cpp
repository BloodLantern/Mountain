#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Collision/ColliderList.hpp"

#include "Mountain/Collision/Circle.hpp"
#include "Mountain/Collision/Grid.hpp"
#include "Mountain/Collision/Hitbox.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Rendering/Draw.hpp"

using namespace Mountain;

ColliderList::ColliderList()
    : Collider(ColliderType::List)
{
}

ColliderList::ColliderList(const std::initializer_list<Collider*> elements)
    : Collider(ColliderType::List)
    , list(elements)
{
}

ColliderList::ColliderList(const Vector2& position, const std::initializer_list<Collider*> elements)  // NOLINT(clang-diagnostic-shadow-field)
    : Collider(ColliderType::List, position)
    , list(elements)
{
}

void ColliderList::RenderDebug(const Color& color) const
{
    Vector2 topLeft = Vector2::One() * std::numeric_limits<float_t>::max(), bottomRight = Vector2::One() * std::numeric_limits<float_t>::min();

    for (const Collider* const c : list)
    {
        topLeft.x = std::min(topLeft.x, c->AbsoluteLeft());
        topLeft.y = std::min(topLeft.y, c->AbsoluteTop());
        bottomRight.x = std::min(bottomRight.x, c->AbsoluteRight());
        bottomRight.y = std::min(bottomRight.y, c->AbsoluteBottom());

        c->RenderDebug(color);
    }

    Draw::Rectangle(topLeft, bottomRight - topLeft, 0.f, Vector2::Zero(), color);
}

bool_t ColliderList::CheckCollision(const Vector2 point) const
{
    return Any(list, [&] (const Collider* c) -> bool_t { return c->CheckCollision(point - GetActualPosition()); });
}

bool_t ColliderList::CheckCollision(const Hitbox& hitbox) const
{
    return Any(list, [&] (const Collider* c) -> bool_t { return c->CheckCollision(hitbox); });
}

bool_t ColliderList::CheckCollision(const Circle& circle) const
{
    return Any(list, [&] (const Collider* c) -> bool_t { return c->CheckCollision(circle); });
}

bool_t ColliderList::CheckCollision(const Grid& grid) const
{
    return Any(list, [&] (const Collider* c) -> bool_t { return c->CheckCollision(grid); });
}

bool_t ColliderList::CheckCollision(const ColliderList& otherList) const
{
    return Any(list, [&] (const Collider* c) -> bool_t { return c->CheckCollision(otherList); });
}

float_t ColliderList::Left() const
{
    float_t left = std::numeric_limits<float_t>::max();
    for (const Collider* const c : list)
        left = std::min(left, c->Left());
    return left;
}

float_t ColliderList::Right() const
{
    float_t right = std::numeric_limits<float_t>::min();
    for (const Collider* const c : list)
        right = std::max(right, c->Right());
    return right;
}

float_t ColliderList::Top() const
{
    float_t top = std::numeric_limits<float_t>::min();
    for (const Collider* const c : list)
        top = std::max(top, c->Top());
    return top;
}

float_t ColliderList::Bottom() const
{
    float_t bottom = std::numeric_limits<float_t>::max();
    for (const Collider* const c : list)
        bottom = std::min(bottom, c->Bottom());
    return bottom;
}

float_t ColliderList::AbsoluteLeft() const
{
    float_t left = std::numeric_limits<float_t>::max();
    for (const Collider* const c : list)
        left = std::min(left, c->AbsoluteLeft());
    return left;
}

float_t ColliderList::AbsoluteRight() const
{
    float_t right = std::numeric_limits<float_t>::min();
    for (const Collider* const c : list)
        right = std::max(right, c->AbsoluteRight());
    return right;
}

float_t ColliderList::AbsoluteTop() const
{
    float_t top = std::numeric_limits<float_t>::min();
    for (const Collider* const c : list)
        top = std::max(top, c->AbsoluteTop());
    return top;
}

float_t ColliderList::AbsoluteBottom() const
{
    float_t bottom = std::numeric_limits<float_t>::max();
    for (const Collider* const c : list)
        bottom = std::min(bottom, c->AbsoluteBottom());
    return bottom;
}

Vector2 ColliderList::AbsoluteCenter() const
{
    Vector2 center;
    for (const Collider* const c : list)
        center += c->AbsoluteCenter();
    return center / static_cast<float_t>(list.GetSize());
}
