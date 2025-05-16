#pragma once

#include "Mountain/Ecs/Entity.hpp"

class TestEntity : public Mountain::Entity
{
public:
    int32_t type = -1;

    explicit TestEntity(const Vector2& pos) : Entity(pos) {}
};
