#include "Mountain/collision/collider_list.hpp"

#include "Mountain/collision/circle.hpp"
#include "Mountain/collision/grid.hpp"
#include "Mountain/collision/hitbox.hpp"
#include "Mountain/rendering/draw.hpp"

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

void ColliderList::DebugRender(const Color& color) const
{
    Vector2 topLeft = Vector2::One() * std::numeric_limits<float_t>::max(), bottomRight = Vector2::One() * std::numeric_limits<float_t>::min();
    
    for (const Collider* const c : list)
    {
        topLeft.x = std::min(topLeft.x, c->Left());
        topLeft.y = std::min(topLeft.y, c->Top());
        bottomRight.x = std::min(bottomRight.x, c->Right());
        bottomRight.y = std::min(bottomRight.y, c->Bottom());
        
        c->DebugRender(color);
    }

    Draw::Rectangle(topLeft, bottomRight - topLeft, color);
}

bool_t ColliderList::CheckCollision(const Vector2& point) const
{
    return std::ranges::any_of(list, [&] (const Collider* const c) -> bool_t { return c->CheckCollision(point - position); });
}

bool_t ColliderList::CheckCollision(const Hitbox& hitbox) const
{
    Hitbox h = hitbox;
    h.position -= position;
    return std::ranges::any_of(list, [&] (const Collider* const c) -> bool_t { return c->CheckCollision(h); });
}

bool_t ColliderList::CheckCollision(const Circle& circle) const
{
    Circle ci = circle;
    ci.position -= position;
    return std::ranges::any_of(list, [&] (const Collider* const c) -> bool_t { return c->CheckCollision(ci); });
}

bool_t ColliderList::CheckCollision(const Grid& grid) const
{
    Grid g = grid;
    g.position -= position;
    return std::ranges::any_of(list, [&] (const Collider* const c) -> bool_t { return c->CheckCollision(g); });
}

bool_t ColliderList::CheckCollision(const ColliderList& otherList) const
{
    for (decltype(list)::ConstIterator it = list.CBegin(); it != list.CEnd(); it++)
    {
		(*it)->position += position;
		const bool_t collision = (*it)->CheckCollision(otherList);
        (*it)->position -= position;

        if (collision)
            return true;
    }
    return false;
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

Vector2 ColliderList::Center() const
{
    Vector2 center;
    for (const Collider* const c : list)
        center += c->Center();
    return center / static_cast<float_t>(list.GetSize());
}
