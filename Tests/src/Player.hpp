#pragma once

#include "Common.hpp"

#include <Mountain/Ecs/Entity.hpp>
#include <Mountain/Ecs/Component/Sprite.hpp>
#include <Mountain/Rendering/LightSource.hpp>

class Player : public Entity
{
public:
    float_t movementSpeed = 150.f;

    LightSource* light;
    Sprite* sprite;

    explicit Player(const Vector2& pos, LightSource& lightSource);

    void LoadResources();
    void Update() override;
    void Render() override;
};
