#include "collider_list.hpp"

#include "hitbox.hpp"
#include "circle.hpp"
#include "grid.hpp"

mountain::ColliderList::ColliderList(std::initializer_list<Collider*> elements)
    : list(elements)
{
}

mountain::ColliderList::ColliderList(const Vector2& position, std::initializer_list<Collider*> elements)
    : Collider(position)
    , list(elements)
{
}

void mountain::ColliderList::Draw(const Color color) const
{
    for (const Collider* const c : list)
        c->Draw(color);
}

bool mountain::ColliderList::CheckCollision(const Vector2& point) const
{
    for (const Collider* const c : list)
    {
        if (c->CheckCollision(point - Position))
            return true;
    }
    return false;
}

bool mountain::ColliderList::CheckCollision(const Hitbox& hitbox) const
{
    Hitbox h = hitbox;
    h.Position -= Position;
    for (const Collider* const c : list)
    {
        if (c->CheckCollision(h))
            return true;
    }
    return false;
}

bool mountain::ColliderList::CheckCollision(const Circle& circle) const
{
    Circle ci = circle;
    ci.Position -= Position;
    for (const Collider* const c : list)
    {
        if (c->CheckCollision(ci))
            return true;
    }
    return false;
}

bool mountain::ColliderList::CheckCollision(const Grid& grid) const
{
    Grid g = grid;
    g.Position -= Position;
    for (const Collider* const c : list)
    {
        if (c->CheckCollision(g))
            return true;
    }
    return false;
}

bool mountain::ColliderList::CheckCollision(const ColliderList& otherList) const
{
    for (decltype(list)::const_iterator it = list.begin(); it != list.end(); it++)
    {
		(*it)->Position += Position;
		const bool collision = (*it)->CheckCollision(otherList);
        (*it)->Position -= Position;

        if (collision)
            return true;
    }
    return false;
}

float mountain::ColliderList::Left() const
{
    float left = std::numeric_limits<float>::max();
    for (const Collider* const c : list)
    {
        left = std::min(left, c->Left());
    }
    return left;
}

float mountain::ColliderList::Right() const
{
    float right = std::numeric_limits<float>::min();
    for (const Collider* const c : list)
    {
        right = std::max(right, c->Right());
    }
    return right;
}

float mountain::ColliderList::Top() const
{
    float top = std::numeric_limits<float>::min();
    for (const Collider* const c : list)
    {
        top = std::max(top, c->Top());
    }
    return top;
}

float mountain::ColliderList::Bottom() const
{
    float bottom = std::numeric_limits<float>::max();
    for (const Collider* const c : list)
    {
        bottom = std::min(bottom, c->Bottom());
    }
    return bottom;
}

Vector2 mountain::ColliderList::Center() const
{
    Vector2 center;
    for (const Collider* const c : list)
    {
        center += c->Center();
    }
    return center / static_cast<float>(list.size());
}
