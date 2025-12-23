

#include "Mountain/Collision/ColliderList.hpp"

#include "Mountain/Collision/Circle.hpp"
#include "Mountain/Collision/Grid.hpp"
#include "Mountain/Collision/Hitbox.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Graphics/Draw.hpp"

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
    Vector2 topLeft = Vector2::One() * std::numeric_limits<f32>::max(), bottomRight = Vector2::One() * std::numeric_limits<f32>::min();

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

bool ColliderList::CheckCollision(const Vector2 point) const
{
    return Any(list, [&] (const Collider* c) -> bool { return c->CheckCollision(point - GetActualPosition()); });
}

bool ColliderList::CheckCollision(const Hitbox& hitbox) const
{
    return Any(list, [&] (const Collider* c) -> bool { return c->CheckCollision(hitbox); });
}

bool ColliderList::CheckCollision(const Circle& circle) const
{
    return Any(list, [&] (const Collider* c) -> bool { return c->CheckCollision(circle); });
}

bool ColliderList::CheckCollision(const Grid& grid) const
{
    return Any(list, [&] (const Collider* c) -> bool { return c->CheckCollision(grid); });
}

bool ColliderList::CheckCollision(const ColliderList& otherList) const
{
    return Any(list, [&] (const Collider* c) -> bool { return c->CheckCollision(otherList); });
}

f32 ColliderList::Left() const
{
    f32 left = std::numeric_limits<f32>::max();
    for (const Collider* const c : list)
        left = std::min(left, c->Left());
    return left;
}

f32 ColliderList::Right() const
{
    f32 right = std::numeric_limits<f32>::min();
    for (const Collider* const c : list)
        right = std::max(right, c->Right());
    return right;
}

f32 ColliderList::Top() const
{
    f32 top = std::numeric_limits<f32>::min();
    for (const Collider* const c : list)
        top = std::max(top, c->Top());
    return top;
}

f32 ColliderList::Bottom() const
{
    f32 bottom = std::numeric_limits<f32>::max();
    for (const Collider* const c : list)
        bottom = std::min(bottom, c->Bottom());
    return bottom;
}

f32 ColliderList::AbsoluteLeft() const
{
    f32 left = std::numeric_limits<f32>::max();
    for (const Collider* const c : list)
        left = std::min(left, c->AbsoluteLeft());
    return left;
}

f32 ColliderList::AbsoluteRight() const
{
    f32 right = std::numeric_limits<f32>::min();
    for (const Collider* const c : list)
        right = std::max(right, c->AbsoluteRight());
    return right;
}

f32 ColliderList::AbsoluteTop() const
{
    f32 top = std::numeric_limits<f32>::min();
    for (const Collider* const c : list)
        top = std::max(top, c->AbsoluteTop());
    return top;
}

f32 ColliderList::AbsoluteBottom() const
{
    f32 bottom = std::numeric_limits<f32>::max();
    for (const Collider* const c : list)
        bottom = std::min(bottom, c->AbsoluteBottom());
    return bottom;
}

Vector2 ColliderList::AbsoluteCenter() const
{
    Vector2 center;
    for (const Collider* const c : list)
        center += c->AbsoluteCenter();
    return center / static_cast<f32>(list.GetSize());
}
