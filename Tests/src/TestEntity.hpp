#pragma once

#include "Mountain/Ecs/Entity.hpp"

class TestEntity : public Mountain::Entity
{
public:
    explicit TestEntity(const Vector2& pos) : Entity(pos) {}
};
